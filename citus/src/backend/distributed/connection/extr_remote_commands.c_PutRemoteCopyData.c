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
struct TYPE_4__ {scalar_t__ copyBytesWrittenSinceLastFlush; int /*<<< orphan*/ * pgConn; } ;
typedef  int /*<<< orphan*/  PGconn ;
typedef  TYPE_1__ MultiConnection ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ CONNECTION_OK ; 
 int FinishConnectionIO (TYPE_1__*,int) ; 
 scalar_t__ MAX_PUT_COPY_DATA_BUFFER_SIZE ; 
 int /*<<< orphan*/  PQisnonblocking (int /*<<< orphan*/ *) ; 
 int PQputCopyData (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ PQstatus (int /*<<< orphan*/ *) ; 

bool
PutRemoteCopyData(MultiConnection *connection, const char *buffer, int nbytes)
{
	PGconn *pgConn = connection->pgConn;
	int copyState = 0;
	bool allowInterrupts = true;

	if (PQstatus(pgConn) != CONNECTION_OK)
	{
		return false;
	}

	Assert(PQisnonblocking(pgConn));

	copyState = PQputCopyData(pgConn, buffer, nbytes);
	if (copyState == -1)
	{
		return false;
	}

	/*
	 * PQputCopyData may have queued up part of the data even if it managed
	 * to send some of it succesfully. We provide back pressure by waiting
	 * until the socket is writable to prevent the internal libpq buffers
	 * from growing excessively.
	 *
	 * We currently allow the internal buffer to grow to 8MB before
	 * providing back pressure based on experimentation that showed
	 * throughput get worse at 4MB and lower due to the number of CPU
	 * cycles spent in networking system calls.
	 */

	connection->copyBytesWrittenSinceLastFlush += nbytes;
	if (connection->copyBytesWrittenSinceLastFlush > MAX_PUT_COPY_DATA_BUFFER_SIZE)
	{
		connection->copyBytesWrittenSinceLastFlush = 0;
		return FinishConnectionIO(connection, allowInterrupts);
	}

	return true;
}