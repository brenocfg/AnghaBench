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
struct bnx2x {int /*<<< orphan*/  rss_conf_obj; } ;

/* Variables and functions */
 int bnx2x_config_rss_pf (struct bnx2x*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int bnx2x_config_rss_eth(struct bnx2x *bp, bool config_hash)
{
	return bnx2x_config_rss_pf(bp, &bp->rss_conf_obj, config_hash);
}