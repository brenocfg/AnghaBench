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
struct xt_rateinfo {int /*<<< orphan*/  master; } ;
struct xt_mtdtor_param {struct xt_rateinfo* matchinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void limit_mt_destroy(const struct xt_mtdtor_param *par)
{
	const struct xt_rateinfo *info = par->matchinfo;

	kfree(info->master);
}