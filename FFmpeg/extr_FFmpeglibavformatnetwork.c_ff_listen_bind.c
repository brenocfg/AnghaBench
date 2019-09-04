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
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  URLContext ;

/* Variables and functions */
 int /*<<< orphan*/  closesocket (int) ; 
 int ff_accept (int,int,int /*<<< orphan*/ *) ; 
 int ff_listen (int,struct sockaddr const*,int /*<<< orphan*/ ) ; 

int ff_listen_bind(int fd, const struct sockaddr *addr,
                   socklen_t addrlen, int timeout, URLContext *h)
{
    int ret;
    if ((ret = ff_listen(fd, addr, addrlen)) < 0)
        return ret;
    if ((ret = ff_accept(fd, timeout, h)) < 0)
        return ret;
    closesocket(fd);
    return ret;
}