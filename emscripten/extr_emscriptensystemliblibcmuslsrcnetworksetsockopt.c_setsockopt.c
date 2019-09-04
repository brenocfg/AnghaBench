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
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int socketcall (int (*) (int,int,int,void const*,int /*<<< orphan*/ ),int,int,int,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen)
{
	return socketcall(setsockopt, fd, level, optname, optval, optlen, 0);
}