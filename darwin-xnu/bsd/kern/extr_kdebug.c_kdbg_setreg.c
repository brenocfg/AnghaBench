#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int type; int value1; int value2; int /*<<< orphan*/  value4; int /*<<< orphan*/  value3; } ;
typedef  TYPE_1__ kd_regtype ;
struct TYPE_5__ {unsigned int kdebug_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KDBG_CKTYPES ; 
#define  KDBG_CLASSTYPE 132 
 int const KDBG_PIDCHECK ; 
 int const KDBG_PIDEXCLUDE ; 
 int const KDBG_RANGECHECK ; 
#define  KDBG_RANGETYPE 131 
#define  KDBG_SUBCLSTYPE 130 
 int const KDBG_TYPEFILTER_CHECK ; 
#define  KDBG_TYPENONE 129 
#define  KDBG_VALCHECK 128 
 int /*<<< orphan*/  SLOW_CHECKS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__ kd_ctrl_page ; 
 int /*<<< orphan*/  kdbg_set_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int kdlog_beg ; 
 unsigned int kdlog_end ; 
 unsigned int kdlog_value1 ; 
 unsigned int kdlog_value2 ; 
 int /*<<< orphan*/  kdlog_value3 ; 
 int /*<<< orphan*/  kdlog_value4 ; 

int
kdbg_setreg(kd_regtype * kdr)
{
	int ret=0;
	unsigned int val_1, val_2, val;
	switch (kdr->type) {
	
	case KDBG_CLASSTYPE :
		val_1 = (kdr->value1 & 0xff);
		val_2 = (kdr->value2 & 0xff);
		kdlog_beg = (val_1<<24);
		kdlog_end = (val_2<<24);
		kd_ctrl_page.kdebug_flags &= (unsigned int)~KDBG_CKTYPES;
		kd_ctrl_page.kdebug_flags &= ~KDBG_VALCHECK;       /* Turn off specific value check  */
		kd_ctrl_page.kdebug_flags |= (KDBG_RANGECHECK | KDBG_CLASSTYPE);
		kdbg_set_flags(SLOW_CHECKS, 0, TRUE);
		break;
	case KDBG_SUBCLSTYPE :
		val_1 = (kdr->value1 & 0xff);
		val_2 = (kdr->value2 & 0xff);
		val = val_2 + 1;
		kdlog_beg = ((val_1<<24) | (val_2 << 16));
		kdlog_end = ((val_1<<24) | (val << 16));
		kd_ctrl_page.kdebug_flags &= (unsigned int)~KDBG_CKTYPES;
		kd_ctrl_page.kdebug_flags &= ~KDBG_VALCHECK;       /* Turn off specific value check  */
		kd_ctrl_page.kdebug_flags |= (KDBG_RANGECHECK | KDBG_SUBCLSTYPE);
		kdbg_set_flags(SLOW_CHECKS, 0, TRUE);
		break;
	case KDBG_RANGETYPE :
		kdlog_beg = (kdr->value1);
		kdlog_end = (kdr->value2);
		kd_ctrl_page.kdebug_flags &= (unsigned int)~KDBG_CKTYPES;
		kd_ctrl_page.kdebug_flags &= ~KDBG_VALCHECK;       /* Turn off specific value check  */
		kd_ctrl_page.kdebug_flags |= (KDBG_RANGECHECK | KDBG_RANGETYPE);
		kdbg_set_flags(SLOW_CHECKS, 0, TRUE);
		break;
	case KDBG_VALCHECK:
		kdlog_value1 = (kdr->value1);
		kdlog_value2 = (kdr->value2);
		kdlog_value3 = (kdr->value3);
		kdlog_value4 = (kdr->value4);
		kd_ctrl_page.kdebug_flags &= (unsigned int)~KDBG_CKTYPES;
		kd_ctrl_page.kdebug_flags &= ~KDBG_RANGECHECK;    /* Turn off range check */
		kd_ctrl_page.kdebug_flags |= KDBG_VALCHECK;       /* Turn on specific value check  */
		kdbg_set_flags(SLOW_CHECKS, 0, TRUE);
		break;
	case KDBG_TYPENONE :
		kd_ctrl_page.kdebug_flags &= (unsigned int)~KDBG_CKTYPES;

		if ( (kd_ctrl_page.kdebug_flags & (KDBG_RANGECHECK | KDBG_VALCHECK   | 
						   KDBG_PIDCHECK   | KDBG_PIDEXCLUDE | 
						   KDBG_TYPEFILTER_CHECK)) )
			kdbg_set_flags(SLOW_CHECKS, 0, TRUE);
		else
			kdbg_set_flags(SLOW_CHECKS, 0, FALSE);

		kdlog_beg = 0;
		kdlog_end = 0;
		break;
	default :
		ret = EINVAL;
		break;
	}
	return(ret);
}