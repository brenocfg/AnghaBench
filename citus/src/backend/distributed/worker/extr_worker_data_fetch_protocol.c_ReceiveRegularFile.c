#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
typedef  scalar_t__ int32 ;
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__* StringInfo ;
typedef  scalar_t__ ResultStatus ;
typedef  scalar_t__ QueryStatus ;
typedef  scalar_t__ CopyStatus ;

/* Variables and functions */
 scalar_t__ BasicOpenFilePerm (char*,int const,int const) ; 
 scalar_t__ CLIENT_COPY_DONE ; 
 scalar_t__ CLIENT_COPY_MORE ; 
 scalar_t__ CLIENT_INVALID_QUERY ; 
 scalar_t__ CLIENT_QUERY_COPY ; 
 scalar_t__ CLIENT_RESULT_BUSY ; 
 scalar_t__ CLIENT_RESULT_READY ; 
 int /*<<< orphan*/  CitusDeleteFile (char*) ; 
 char* CurrentDatabaseName () ; 
 int /*<<< orphan*/  DEBUG2 ; 
 scalar_t__ INVALID_CONNECTION_ID ; 
 int MAXPGPATH ; 
 scalar_t__ MultiClientConnect (char const*,int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ MultiClientCopyData (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MultiClientDisconnect (scalar_t__) ; 
 scalar_t__ MultiClientQueryStatus (scalar_t__) ; 
 scalar_t__ MultiClientResultStatus (scalar_t__) ; 
 int MultiClientSendQuery (scalar_t__,char*) ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int PG_BINARY ; 
 int /*<<< orphan*/  ReceiveResourceCleanup (scalar_t__,char*,scalar_t__) ; 
 long RemoteTaskCheckInterval ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  WARNING ; 
 int close (scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 int /*<<< orphan*/  pg_usleep (long) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static bool
ReceiveRegularFile(const char *nodeName, uint32 nodePort, const char *nodeUser,
				   StringInfo transmitCommand, StringInfo filePath)
{
	int32 fileDescriptor = -1;
	char filename[MAXPGPATH];
	int closed = -1;
	const int fileFlags = (O_APPEND | O_CREAT | O_RDWR | O_TRUNC | PG_BINARY);
	const int fileMode = (S_IRUSR | S_IWUSR);

	QueryStatus queryStatus = CLIENT_INVALID_QUERY;
	int32 connectionId = INVALID_CONNECTION_ID;
	char *nodeDatabase = NULL;
	bool querySent = false;
	bool queryReady = false;
	bool copyDone = false;

	/* create local file to append remote data to */
	snprintf(filename, MAXPGPATH, "%s", filePath->data);

	fileDescriptor = BasicOpenFilePerm(filename, fileFlags, fileMode);
	if (fileDescriptor < 0)
	{
		ereport(WARNING, (errcode_for_file_access(),
						  errmsg("could not open file \"%s\": %m", filePath->data)));

		return false;
	}

	/* we use the same database name on the master and worker nodes */
	nodeDatabase = CurrentDatabaseName();

	/* connect to remote node */
	connectionId = MultiClientConnect(nodeName, nodePort, nodeDatabase, nodeUser);
	if (connectionId == INVALID_CONNECTION_ID)
	{
		ReceiveResourceCleanup(connectionId, filename, fileDescriptor);

		return false;
	}

	/* send request to remote node to start transmitting data */
	querySent = MultiClientSendQuery(connectionId, transmitCommand->data);
	if (!querySent)
	{
		ReceiveResourceCleanup(connectionId, filename, fileDescriptor);

		return false;
	}

	/* loop until the remote node acknowledges our transmit request */
	while (!queryReady)
	{
		ResultStatus resultStatus = MultiClientResultStatus(connectionId);
		if (resultStatus == CLIENT_RESULT_READY)
		{
			queryReady = true;
		}
		else if (resultStatus == CLIENT_RESULT_BUSY)
		{
			/* remote node did not respond; wait for longer */
			long sleepIntervalPerCycle = RemoteTaskCheckInterval * 1000L;
			pg_usleep(sleepIntervalPerCycle);
		}
		else
		{
			ReceiveResourceCleanup(connectionId, filename, fileDescriptor);

			return false;
		}
	}

	/* check query response is as expected */
	queryStatus = MultiClientQueryStatus(connectionId);
	if (queryStatus != CLIENT_QUERY_COPY)
	{
		ReceiveResourceCleanup(connectionId, filename, fileDescriptor);

		return false;
	}

	/* loop until we receive and append all the data from remote node */
	while (!copyDone)
	{
		CopyStatus copyStatus = MultiClientCopyData(connectionId, fileDescriptor, NULL);
		if (copyStatus == CLIENT_COPY_DONE)
		{
			copyDone = true;
		}
		else if (copyStatus == CLIENT_COPY_MORE)
		{
			/* remote node will continue to send more data */
		}
		else
		{
			ReceiveResourceCleanup(connectionId, filename, fileDescriptor);

			return false;
		}
	}

	/* we are done executing; release the connection and the file handle */
	MultiClientDisconnect(connectionId);

	closed = close(fileDescriptor);
	if (closed < 0)
	{
		ereport(WARNING, (errcode_for_file_access(),
						  errmsg("could not close file \"%s\": %m", filename)));

		/* if we failed to close file, try to delete it before erroring out */
		CitusDeleteFile(filename);

		return false;
	}

	/* we successfully received the remote file */
	ereport(DEBUG2, (errmsg("received remote file \"%s\"", filename)));

	return true;
}