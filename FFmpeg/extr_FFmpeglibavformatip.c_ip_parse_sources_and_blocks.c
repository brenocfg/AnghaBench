#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nb_exclude_addrs; scalar_t__ nb_include_addrs; int /*<<< orphan*/  exclude_addrs; int /*<<< orphan*/  include_addrs; } ;
typedef  TYPE_1__ IPSourceFilters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 
 int ip_parse_addr_list (void*,char const*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static int ip_parse_sources_and_blocks(void *log_ctx, const char *buf, IPSourceFilters *filters, int parse_include_list)
{
    int ret;
    if (parse_include_list)
        ret = ip_parse_addr_list(log_ctx, buf, &filters->include_addrs, &filters->nb_include_addrs);
    else
        ret = ip_parse_addr_list(log_ctx, buf, &filters->exclude_addrs, &filters->nb_exclude_addrs);

    if (ret >= 0 && filters->nb_include_addrs && filters->nb_exclude_addrs) {
        av_log(log_ctx, AV_LOG_ERROR, "Simultaneously including and excluding sources is not supported.\n");
        return AVERROR(EINVAL);
    }
    return ret;
}