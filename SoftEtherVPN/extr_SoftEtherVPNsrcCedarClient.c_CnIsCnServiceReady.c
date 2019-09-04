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
typedef  int /*<<< orphan*/  SOCK ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_NOTIFY_PORT ; 
 int CnCheckAlreadyExists (int) ; 
 int /*<<< orphan*/ * ConnectEx (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 

bool CnIsCnServiceReady()
{
	SOCK *s;
	// Confirm running the notification service
	if (CnCheckAlreadyExists(false) == false)
	{
		// Not running
		return false;
	}

	// Try to connect to the TCP port
	s = ConnectEx("localhost", CLIENT_NOTIFY_PORT, 500);
	if (s == NULL)
	{
		// The TCP port is not opened
		return false;
	}

	Disconnect(s);
	ReleaseSock(s);

	// Running
	return true;
}