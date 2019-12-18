#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {scalar_t__ sa_family; scalar_t__ ss_family; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_3__ sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; scalar_t__ ss_family; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct ip_mreq_source {TYPE_2__ imr_sourceaddr; TYPE_3__ imr_interface; TYPE_1__ imr_multiaddr; } ;
struct group_source_req {int /*<<< orphan*/  gsr_source; int /*<<< orphan*/  gsr_group; scalar_t__ gsr_interface; } ;
typedef  int /*<<< orphan*/  mreqs ;
typedef  int /*<<< orphan*/  URLContext ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int IPPROTO_IP ; 
 int IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IP_ADD_SOURCE_MEMBERSHIP ; 
 int /*<<< orphan*/  IP_BLOCK_SOURCE ; 
 int /*<<< orphan*/  MCAST_BLOCK_SOURCE ; 
 int /*<<< orphan*/  MCAST_JOIN_SOURCE_GROUP ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ff_log_net_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int ff_neterrno () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sockaddr_storage*,int) ; 
 scalar_t__ setsockopt (int,int,int /*<<< orphan*/ ,void const*,int) ; 

__attribute__((used)) static int udp_set_multicast_sources(URLContext *h,
                                     int sockfd, struct sockaddr *addr,
                                     int addr_len, struct sockaddr_storage *local_addr,
                                     struct sockaddr_storage *sources,
                                     int nb_sources, int include)
{
    int i;
    if (addr->sa_family != AF_INET) {
#if HAVE_STRUCT_GROUP_SOURCE_REQ && defined(MCAST_BLOCK_SOURCE)
        /* For IPv4 prefer the old approach, as that alone works reliably on
         * Windows and it also supports supplying the interface based on its
         * address. */
        int i;
        for (i = 0; i < nb_sources; i++) {
            struct group_source_req mreqs;
            int level = addr->sa_family == AF_INET ? IPPROTO_IP : IPPROTO_IPV6;

            //TODO: Interface index should be looked up from local_addr
            mreqs.gsr_interface = 0;
            memcpy(&mreqs.gsr_group, addr, addr_len);
            memcpy(&mreqs.gsr_source, &sources[i], sizeof(*sources));

            if (setsockopt(sockfd, level,
                           include ? MCAST_JOIN_SOURCE_GROUP : MCAST_BLOCK_SOURCE,
                           (const void *)&mreqs, sizeof(mreqs)) < 0) {
                if (include)
                    ff_log_net_error(NULL, AV_LOG_ERROR, "setsockopt(MCAST_JOIN_SOURCE_GROUP)");
                else
                    ff_log_net_error(NULL, AV_LOG_ERROR, "setsockopt(MCAST_BLOCK_SOURCE)");
                return ff_neterrno();
            }
        }
        return 0;
#else
        av_log(h, AV_LOG_ERROR,
               "Setting multicast sources only supported for IPv4\n");
        return AVERROR(EINVAL);
#endif
    }
#if HAVE_STRUCT_IP_MREQ_SOURCE && defined(IP_BLOCK_SOURCE)
    for (i = 0; i < nb_sources; i++) {
        struct ip_mreq_source mreqs;
        if (sources[i].ss_family != AF_INET) {
            av_log(h, AV_LOG_ERROR, "Source/block address %d is of incorrect protocol family\n", i + 1);
            return AVERROR(EINVAL);
        }

        mreqs.imr_multiaddr.s_addr = ((struct sockaddr_in *)addr)->sin_addr.s_addr;
        if (local_addr)
            mreqs.imr_interface= ((struct sockaddr_in *)local_addr)->sin_addr;
        else
            mreqs.imr_interface.s_addr= INADDR_ANY;
        mreqs.imr_sourceaddr.s_addr = ((struct sockaddr_in *)&sources[i])->sin_addr.s_addr;

        if (setsockopt(sockfd, IPPROTO_IP,
                       include ? IP_ADD_SOURCE_MEMBERSHIP : IP_BLOCK_SOURCE,
                       (const void *)&mreqs, sizeof(mreqs)) < 0) {
            if (include)
                ff_log_net_error(h, AV_LOG_ERROR, "setsockopt(IP_ADD_SOURCE_MEMBERSHIP)");
            else
                ff_log_net_error(h, AV_LOG_ERROR, "setsockopt(IP_BLOCK_SOURCE)");
            return ff_neterrno();
        }
    }
#else
    return AVERROR(ENOSYS);
#endif
    return 0;
}