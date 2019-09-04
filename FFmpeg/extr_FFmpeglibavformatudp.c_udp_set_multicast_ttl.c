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

/* Variables and functions */

__attribute__((used)) static int udp_set_multicast_ttl(int sockfd, int mcastTTL,
                                 struct sockaddr *addr)
{
#ifdef IP_MULTICAST_TTL
    if (addr->sa_family == AF_INET) {
        if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, &mcastTTL, sizeof(mcastTTL)) < 0) {
            ff_log_net_error(NULL, AV_LOG_ERROR, "setsockopt(IP_MULTICAST_TTL)");
            return -1;
        }
    }
#endif
#if defined(IPPROTO_IPV6) && defined(IPV6_MULTICAST_HOPS)
    if (addr->sa_family == AF_INET6) {
        if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_MULTICAST_HOPS, &mcastTTL, sizeof(mcastTTL)) < 0) {
            ff_log_net_error(NULL, AV_LOG_ERROR, "setsockopt(IPV6_MULTICAST_HOPS)");
            return -1;
        }
    }
#endif
    return 0;
}