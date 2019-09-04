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
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 scalar_t__ socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool IsIPv6Supported()
{
#ifdef	NO_IPV6
	return false;
#else	// NO_IPV6
	SOCKET s;

	s = socket(AF_INET6, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET)
	{
		return false;
	}

	closesocket(s);

	return true;
#endif	// NO_IPV6
}