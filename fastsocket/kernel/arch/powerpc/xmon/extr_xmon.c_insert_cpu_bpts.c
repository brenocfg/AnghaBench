#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int enabled; int address; } ;
struct TYPE_3__ {int address; int enabled; } ;

/* Variables and functions */
 int BP_IABR ; 
 int BP_IABR_TE ; 
 int /*<<< orphan*/  CPU_FTR_IABR ; 
 int /*<<< orphan*/  SPRN_IABR ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 TYPE_2__ dabr ; 
 TYPE_1__* iabr ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dabr (int) ; 

__attribute__((used)) static void insert_cpu_bpts(void)
{
	if (dabr.enabled)
		set_dabr(dabr.address | (dabr.enabled & 7));
	if (iabr && cpu_has_feature(CPU_FTR_IABR))
		mtspr(SPRN_IABR, iabr->address
			 | (iabr->enabled & (BP_IABR|BP_IABR_TE)));
}