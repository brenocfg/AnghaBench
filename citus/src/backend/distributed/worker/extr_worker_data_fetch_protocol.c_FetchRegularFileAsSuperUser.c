#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32 ;
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  ATTEMPT_FILE_SUFFIX ; 
 char* CitusExtensionOwnerName () ; 
 char* CurrentUserName () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  MIN_TASK_FILENAME_WIDTH ; 
 int ReceiveRegularFile (char const*,int /*<<< orphan*/ ,char*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TRANSMIT_WITH_USER_COMMAND ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,char const*,...) ; 
 TYPE_1__* makeStringInfo () ; 
 int /*<<< orphan*/  quote_literal_cstr (char*) ; 
 int /*<<< orphan*/  random () ; 
 int rename (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
FetchRegularFileAsSuperUser(const char *nodeName, uint32 nodePort,
							StringInfo remoteFilename, StringInfo localFilename)
{
	char *nodeUser = NULL;
	StringInfo attemptFilename = NULL;
	StringInfo transmitCommand = NULL;
	char *userName = CurrentUserName();
	uint32 randomId = (uint32) random();
	bool received = false;
	int renamed = 0;

	/*
	 * We create an attempt file to signal that the file is still in transit. We
	 * further append a random id to the filename to handle the unexpected case
	 * of another process concurrently fetching the same file.
	 */
	attemptFilename = makeStringInfo();
	appendStringInfo(attemptFilename, "%s_%0*u%s", localFilename->data,
					 MIN_TASK_FILENAME_WIDTH, randomId, ATTEMPT_FILE_SUFFIX);

	transmitCommand = makeStringInfo();
	appendStringInfo(transmitCommand, TRANSMIT_WITH_USER_COMMAND, remoteFilename->data,
					 quote_literal_cstr(userName));

	/* connect as superuser to give file access */
	nodeUser = CitusExtensionOwnerName();

	received = ReceiveRegularFile(nodeName, nodePort, nodeUser, transmitCommand,
								  attemptFilename);
	if (!received)
	{
		ereport(ERROR, (errmsg("could not receive file \"%s\" from %s:%u",
							   remoteFilename->data, nodeName, nodePort)));
	}

	/* atomically rename the attempt file */
	renamed = rename(attemptFilename->data, localFilename->data);
	if (renamed != 0)
	{
		ereport(ERROR, (errcode_for_file_access(),
						errmsg("could not rename file \"%s\" to \"%s\": %m",
							   attemptFilename->data, localFilename->data)));
	}
}