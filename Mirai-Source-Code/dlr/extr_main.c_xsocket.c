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

/* Variables and functions */
 int /*<<< orphan*/  SCN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_socket ; 
 int /*<<< orphan*/  SYS_socketcall ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int syscall (int /*<<< orphan*/ ,int,...) ; 

int xsocket(int domain, int type, int protocol)
{
#if defined(__NR_socketcall)
#ifdef DEBUG
    printf("socket using socketcall\n");
#endif
    struct {
        int domain, type, protocol;
    } socketcall;
    socketcall.domain = domain;
    socketcall.type = type;
    socketcall.protocol = protocol;

    // 1 == SYS_SOCKET
    int ret = syscall(SCN(SYS_socketcall), 1, &socketcall);

#ifdef DEBUG
    printf("socket got ret: %d\n", ret);
#endif
     return ret;
#else
#ifdef DEBUG
    printf("socket using socket\n");
#endif
    return syscall(SCN(SYS_socket), domain, type, protocol);
#endif
}