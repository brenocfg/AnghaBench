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
struct TYPE_2__ {int /*<<< orphan*/  index; } ;
struct xt_set_info_match_v0 {TYPE_1__ match_set; } ;
struct xt_mtdtor_param {struct xt_set_info_match_v0* matchinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ip_set_nfnl_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_match_v0_destroy(const struct xt_mtdtor_param *par)
{
	struct xt_set_info_match_v0 *info = par->matchinfo;

	ip_set_nfnl_put(info->match_set.index);
}