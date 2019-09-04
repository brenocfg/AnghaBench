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
typedef  int /*<<< orphan*/  reuse ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int bind (int,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int ff_neterrno () ; 
 int listen (int,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int ff_listen(int fd, const struct sockaddr *addr,
              socklen_t addrlen)
{
    int ret;
    int reuse = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))) {
        av_log(NULL, AV_LOG_WARNING, "setsockopt(SO_REUSEADDR) failed\n");
    }
    ret = bind(fd, addr, addrlen);
    if (ret)
        return ff_neterrno();

    ret = listen(fd, 1);
    if (ret)
        return ff_neterrno();
    return ret;
}