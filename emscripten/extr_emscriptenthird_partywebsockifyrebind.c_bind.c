#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_2__ {int s_addr; } ;
struct sockaddr_in {int sin_port; scalar_t__ sin_family; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  addr_tmp ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  DEBUG (char*,int,int,int,...) ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  RTLD_NEXT ; 
 scalar_t__ dlsym (int /*<<< orphan*/ ,char*) ; 
 char* getenv (char*) ; 
 int htonl (int /*<<< orphan*/ ) ; 
 void* htons (int) ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_in*,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  ntohl (int) ; 
 int strtol (char*,char**,int) ; 

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    static void * (*func)();
    int do_move = 0;
    struct sockaddr_in * addr_in = (struct sockaddr_in *)addr;
    struct sockaddr_in addr_tmp;
    socklen_t addrlen_tmp;
    char * PORT_OLD, * PORT_NEW, * end1, * end2;
    int ret, oldport, newport, askport = htons(addr_in->sin_port);
    uint32_t askaddr = htons(addr_in->sin_addr.s_addr);
    if (!func) func = (void *(*)()) dlsym(RTLD_NEXT, "bind");

    DEBUG(">> bind(%d, _, %d), askaddr %d, askport %d\n",
          sockfd, addrlen, askaddr, askport);

    /* Determine if we should move this socket */
    if (addr_in->sin_family == AF_INET) {
        // TODO: support IPv6
        PORT_OLD = getenv("REBIND_OLD_PORT");
        PORT_NEW = getenv("REBIND_NEW_PORT");
        if (PORT_OLD && (*PORT_OLD != '\0') &&
            PORT_NEW && (*PORT_NEW != '\0')) {
            oldport = strtol(PORT_OLD, &end1, 10);
            newport = strtol(PORT_NEW, &end2, 10);
            if (oldport && (*end1 == '\0') &&
                newport && (*end2 == '\0') &&
                (oldport == askport)) {
                do_move = 1;
            }
        }
    }

    if (! do_move) {
        /* Just pass everything right through to the real bind */
        ret = (long) func(sockfd, addr, addrlen);
        DEBUG("<< bind(%d, _, %d) ret %d\n", sockfd, addrlen, ret);
        return ret;
    }

    DEBUG("binding fd %d on localhost:%d instead of 0x%x:%d\n",
        sockfd, newport, ntohl(addr_in->sin_addr.s_addr), oldport);

    /* Use a temporary location for the new address information */
    addrlen_tmp = sizeof(addr_tmp);
    memcpy(&addr_tmp, addr, addrlen_tmp);

    /* Bind to other port on the loopback instead */
    addr_tmp.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    addr_tmp.sin_port = htons(newport);
    ret = (long) func(sockfd, &addr_tmp, addrlen_tmp);

    DEBUG("<< bind(%d, _, %d) ret %d\n", sockfd, addrlen, ret);
    return ret;
}