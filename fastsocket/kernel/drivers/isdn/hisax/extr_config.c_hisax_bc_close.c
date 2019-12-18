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
struct hisax_b_if {int dummy; } ;
struct TYPE_2__ {struct hisax_b_if* b_if; } ;
struct BCState {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_L2L1 (struct hisax_b_if*,int,int /*<<< orphan*/ *) ; 
 int PH_DEACTIVATE ; 
 int REQUEST ; 

__attribute__((used)) static void hisax_bc_close(struct BCState *bcs)
{
	struct hisax_b_if *b_if = bcs->hw.b_if;

	if (b_if)
		B_L2L1(b_if, PH_DEACTIVATE | REQUEST, NULL);
}