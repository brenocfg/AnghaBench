#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ int32 ;

/* Variables and functions */
 scalar_t__ INVALID_CONNECTION_ID ; 
 int /*<<< orphan*/  MultiClientDisconnect (scalar_t__) ; 
 int /*<<< orphan*/  WARNING ; 
 int close (scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode_for_file_access () ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 int unlink (char const*) ; 

__attribute__((used)) static void
ReceiveResourceCleanup(int32 connectionId, const char *filename, int32 fileDescriptor)
{
	if (connectionId != INVALID_CONNECTION_ID)
	{
		MultiClientDisconnect(connectionId);
	}

	if (fileDescriptor != -1)
	{
		int closed = -1;
		int deleted = -1;

		closed = close(fileDescriptor);
		if (closed < 0)
		{
			ereport(WARNING, (errcode_for_file_access(),
							  errmsg("could not close file \"%s\": %m", filename)));
		}

		deleted = unlink(filename);
		if (deleted != 0)
		{
			ereport(WARNING, (errcode_for_file_access(),
							  errmsg("could not delete file \"%s\": %m", filename)));
		}
	}
}