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
typedef  int u_long ;

/* Variables and functions */
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_NBIO ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 scalar_t__ ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

bool socket_nonblock(int fd)
{
#if defined(__CELLOS_LV2__) || defined(VITA) || defined(WIIU)
   int i = 1;
   setsockopt(fd, SOL_SOCKET, SO_NBIO, &i, sizeof(int));
   return true;
#elif defined(_WIN32)
   u_long mode = 1;
   return ioctlsocket(fd, FIONBIO, &mode) == 0;
#else
   return fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK) == 0;
#endif
}