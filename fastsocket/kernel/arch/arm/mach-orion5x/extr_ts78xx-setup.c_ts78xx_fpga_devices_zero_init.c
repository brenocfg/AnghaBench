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
struct TYPE_8__ {scalar_t__ init; } ;
struct TYPE_7__ {scalar_t__ init; } ;
struct TYPE_6__ {scalar_t__ init; } ;
struct TYPE_9__ {TYPE_3__ ts_rng; TYPE_2__ ts_nand; TYPE_1__ ts_rtc; } ;
struct TYPE_10__ {TYPE_4__ supports; } ;

/* Variables and functions */
 TYPE_5__ ts78xx_fpga ; 

__attribute__((used)) static void ts78xx_fpga_devices_zero_init(void)
{
	ts78xx_fpga.supports.ts_rtc.init = 0;
	ts78xx_fpga.supports.ts_nand.init = 0;
	ts78xx_fpga.supports.ts_rng.init = 0;
}