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
typedef  int /*<<< orphan*/  IPSourceFilters ;

/* Variables and functions */
 int ip_parse_sources_and_blocks (void*,char const*,int /*<<< orphan*/ *,int) ; 

int ff_ip_parse_sources(void *log_ctx, const char *buf, IPSourceFilters *filters)
{
    return ip_parse_sources_and_blocks(log_ctx, buf, filters, 1);
}