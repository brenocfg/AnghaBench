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
typedef  int UINT ;
typedef  int /*<<< orphan*/  SOCK ;

/* Variables and functions */
 int /*<<< orphan*/ * ConnectEx (char*,int,int) ; 
 int /*<<< orphan*/  Disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSock (int /*<<< orphan*/ *) ; 
 int TIMEOUT_TCP_PORT_CHECK ; 

bool CheckTCPPortEx(char *hostname, UINT port, UINT timeout)
{
	SOCK *s;
	// Validate arguments
	if (hostname == NULL || port == 0 || port >= 65536)
	{
		return false;
	}

	if (timeout == 0)
	{
		timeout = TIMEOUT_TCP_PORT_CHECK;
	}

	s = ConnectEx(hostname, port, timeout);
	if (s == NULL)
	{
		return false;
	}
	else
	{
		Disconnect(s);
		ReleaseSock(s);
		return true;
	}
}