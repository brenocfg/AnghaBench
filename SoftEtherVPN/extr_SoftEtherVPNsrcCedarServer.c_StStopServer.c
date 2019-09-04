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

/* Variables and functions */
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiReleaseServer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopCedarLog () ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * server ; 
 int /*<<< orphan*/  server_lock ; 

void StStopServer()
{
	Lock(server_lock);
	{
		if (server == NULL)
		{
			// Not started
			Unlock(server_lock);
			return;
		}

		// Release the server
		SiReleaseServer(server);
		server = NULL;
	}
	Unlock(server_lock);

	StopCedarLog();
}