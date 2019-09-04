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
struct addrinfo {struct addrinfo* ai_next; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; } ;
typedef  int /*<<< orphan*/  portbuf ;
typedef  int /*<<< orphan*/  hostbuf ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  getnameinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 

__attribute__((used)) static void print_address_list(void *ctx, const struct addrinfo *addr,
                               const char *title)
{
    char hostbuf[100], portbuf[20];
    av_log(ctx, AV_LOG_DEBUG, "%s:\n", title);
    while (addr) {
        getnameinfo(addr->ai_addr, addr->ai_addrlen,
                    hostbuf, sizeof(hostbuf), portbuf, sizeof(portbuf),
                    NI_NUMERICHOST | NI_NUMERICSERV);
        av_log(ctx, AV_LOG_DEBUG, "Address %s port %s\n", hostbuf, portbuf);
        addr = addr->ai_next;
    }
}