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
struct xt_rateest_match_info {scalar_t__ est2; scalar_t__ est1; } ;
struct xt_mtdtor_param {struct xt_rateest_match_info* matchinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  xt_rateest_put (scalar_t__) ; 

__attribute__((used)) static void xt_rateest_mt_destroy(const struct xt_mtdtor_param *par)
{
	struct xt_rateest_match_info *info = par->matchinfo;

	xt_rateest_put(info->est1);
	if (info->est2)
		xt_rateest_put(info->est2);
}