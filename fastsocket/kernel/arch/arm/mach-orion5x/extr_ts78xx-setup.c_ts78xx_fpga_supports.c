#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int present; } ;
struct TYPE_6__ {int present; } ;
struct TYPE_8__ {int present; } ;
struct TYPE_9__ {TYPE_2__ ts_rng; TYPE_1__ ts_nand; TYPE_3__ ts_rtc; } ;
struct TYPE_10__ {int id; TYPE_4__ supports; } ;

/* Variables and functions */
#define  TS7800_REV_1 132 
#define  TS7800_REV_2 131 
#define  TS7800_REV_3 130 
#define  TS7800_REV_4 129 
#define  TS7800_REV_5 128 
 TYPE_5__ ts78xx_fpga ; 

__attribute__((used)) static void ts78xx_fpga_supports(void)
{
	/* TODO: put this 'table' into ts78xx-fpga.h */
	switch (ts78xx_fpga.id) {
	case TS7800_REV_1:
	case TS7800_REV_2:
	case TS7800_REV_3:
	case TS7800_REV_4:
	case TS7800_REV_5:
		ts78xx_fpga.supports.ts_rtc.present = 1;
		ts78xx_fpga.supports.ts_nand.present = 1;
		ts78xx_fpga.supports.ts_rng.present = 1;
		break;
	default:
		ts78xx_fpga.supports.ts_rtc.present = 0;
		ts78xx_fpga.supports.ts_nand.present = 0;
		ts78xx_fpga.supports.ts_rng.present = 0;
	}
}