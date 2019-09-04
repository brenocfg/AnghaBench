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
struct sockaddr_in {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_connect ; 
 int syscall (int /*<<< orphan*/ ,int,struct sockaddr_in*,int) ; 

int xconnect(int fd, struct sockaddr_in *addr, int len)
{
#if defined(__NR_socketcall)
#ifdef DEBUG
    printf("connect using socketcall\n");
#endif
    struct {
        int fd;
        struct sockaddr_in *addr;
        int len;
    } socketcall;
    socketcall.fd = fd;
    socketcall.addr = addr;
    socketcall.len = len;
    // 3 == SYS_CONNECT
    int ret = syscall(SCN(SYS_socketcall), 3, &socketcall);

#ifdef DEBUG
    printf("connect got ret: %d\n", ret);
#endif

    return ret;
#else
#ifdef DEBUG
    printf("connect using connect\n");
#endif
    return syscall(SCN(SYS_connect), fd, addr, len);
#endif
}