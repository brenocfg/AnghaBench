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
typedef  int /*<<< orphan*/  WSADATA ;

/* Variables and functions */
 int /*<<< orphan*/  G_STRLOC ; 
 int /*<<< orphan*/  MAKEWORD (int,int) ; 
 scalar_t__ WSAStartup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_critical (char*,int /*<<< orphan*/ ) ; 

int chassis_frontend_init_win32() {
#ifdef _WIN32
	WSADATA wsaData;

	if (0 != WSAStartup(MAKEWORD( 2, 2 ), &wsaData)) {
		g_critical("%s: WSAStartup(2, 2) failed to initialize the socket library",
				G_STRLOC);

		return -1;
	}

	return 0;
#else
	return -1;
#endif
}