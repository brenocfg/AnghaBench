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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  socketcall_cp (int /*<<< orphan*/  (*) (int,void const*,size_t,int,struct sockaddr const*,int /*<<< orphan*/ ),int,void const*,size_t,int,struct sockaddr const*,int /*<<< orphan*/ ) ; 

ssize_t sendto(int fd, const void *buf, size_t len, int flags, const struct sockaddr *addr, socklen_t alen)
{
	return socketcall_cp(sendto, fd, buf, len, flags, addr, alen);
}