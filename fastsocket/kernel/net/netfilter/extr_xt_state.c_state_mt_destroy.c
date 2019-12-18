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
struct xt_mtdtor_param {TYPE_1__* match; } ;
struct TYPE_2__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 int /*<<< orphan*/  nf_ct_l3proto_module_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void state_mt_destroy(const struct xt_mtdtor_param *par)
{
	nf_ct_l3proto_module_put(par->match->family);
}