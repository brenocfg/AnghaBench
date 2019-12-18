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
typedef  int u32 ;
struct tc_u_common {int hgenerator; } ;

/* Variables and functions */
 scalar_t__ u32_lookup_ht (struct tc_u_common*,int) ; 

__attribute__((used)) static u32 gen_new_htid(struct tc_u_common *tp_c)
{
	int i = 0x800;

	do {
		if (++tp_c->hgenerator == 0x7FF)
			tp_c->hgenerator = 1;
	} while (--i>0 && u32_lookup_ht(tp_c, (tp_c->hgenerator|0x800)<<20));

	return i > 0 ? (tp_c->hgenerator|0x800)<<20 : 0;
}