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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  QE_CR_SUBBLOCK_INVALID ; 
 int /*<<< orphan*/  QE_CR_SUBBLOCK_UCCSLOW1 ; 
 int /*<<< orphan*/  QE_CR_SUBBLOCK_UCCSLOW2 ; 
 int /*<<< orphan*/  QE_CR_SUBBLOCK_UCCSLOW3 ; 
 int /*<<< orphan*/  QE_CR_SUBBLOCK_UCCSLOW4 ; 
 int /*<<< orphan*/  QE_CR_SUBBLOCK_UCCSLOW5 ; 
 int /*<<< orphan*/  QE_CR_SUBBLOCK_UCCSLOW6 ; 
 int /*<<< orphan*/  QE_CR_SUBBLOCK_UCCSLOW7 ; 
 int /*<<< orphan*/  QE_CR_SUBBLOCK_UCCSLOW8 ; 

u32 ucc_slow_get_qe_cr_subblock(int uccs_num)
{
	switch (uccs_num) {
	case 0: return QE_CR_SUBBLOCK_UCCSLOW1;
	case 1: return QE_CR_SUBBLOCK_UCCSLOW2;
	case 2: return QE_CR_SUBBLOCK_UCCSLOW3;
	case 3: return QE_CR_SUBBLOCK_UCCSLOW4;
	case 4: return QE_CR_SUBBLOCK_UCCSLOW5;
	case 5: return QE_CR_SUBBLOCK_UCCSLOW6;
	case 6: return QE_CR_SUBBLOCK_UCCSLOW7;
	case 7: return QE_CR_SUBBLOCK_UCCSLOW8;
	default: return QE_CR_SUBBLOCK_INVALID;
	}
}