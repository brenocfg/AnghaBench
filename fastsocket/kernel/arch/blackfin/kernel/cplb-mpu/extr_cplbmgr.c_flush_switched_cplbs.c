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
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ DCPLB_DATA0 ; 
 scalar_t__ ICPLB_DATA0 ; 
 int MAX_CPLBS ; 
 int /*<<< orphan*/  _disable_dcplb () ; 
 int /*<<< orphan*/  _disable_icplb () ; 
 int /*<<< orphan*/  _enable_dcplb () ; 
 int /*<<< orphan*/  _enable_icplb () ; 
 int /*<<< orphan*/  bfin_write32 (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__** dcplb_tbl ; 
 int first_switched_dcplb ; 
 int first_switched_icplb ; 
 TYPE_1__** icplb_tbl ; 
 int /*<<< orphan*/  local_irq_restore_hw (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save_hw (unsigned long) ; 
 int /*<<< orphan*/ * nr_cplb_flush ; 

void flush_switched_cplbs(unsigned int cpu)
{
	int i;
	unsigned long flags;

	nr_cplb_flush[cpu]++;

	local_irq_save_hw(flags);
	_disable_icplb();
	for (i = first_switched_icplb; i < MAX_CPLBS; i++) {
		icplb_tbl[cpu][i].data = 0;
		bfin_write32(ICPLB_DATA0 + i * 4, 0);
	}
	_enable_icplb();

	_disable_dcplb();
	for (i = first_switched_dcplb; i < MAX_CPLBS; i++) {
		dcplb_tbl[cpu][i].data = 0;
		bfin_write32(DCPLB_DATA0 + i * 4, 0);
	}
	_enable_dcplb();
	local_irq_restore_hw(flags);

}