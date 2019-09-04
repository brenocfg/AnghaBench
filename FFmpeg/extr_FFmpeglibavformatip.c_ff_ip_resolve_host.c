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
struct addrinfo {int ai_socktype; int ai_family; int ai_flags; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  sport ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

struct addrinfo *ff_ip_resolve_host(void *log_ctx,
                                    const char *hostname, int port,
                                    int type, int family, int flags)
{
    struct addrinfo hints = { 0 }, *res = 0;
    int error;
    char sport[16];
    const char *node = 0, *service = "0";

    if (port > 0) {
        snprintf(sport, sizeof(sport), "%d", port);
        service = sport;
    }
    if ((hostname) && (hostname[0] != '\0') && (hostname[0] != '?')) {
        node = hostname;
    }
    hints.ai_socktype = type;
    hints.ai_family   = family;
    hints.ai_flags    = flags;
    if ((error = getaddrinfo(node, service, &hints, &res))) {
        res = NULL;
        av_log(log_ctx, AV_LOG_ERROR, "getaddrinfo(%s, %s): %s\n",
               node ? node : "unknown",
               service,
               gai_strerror(error));
    }

    return res;
}