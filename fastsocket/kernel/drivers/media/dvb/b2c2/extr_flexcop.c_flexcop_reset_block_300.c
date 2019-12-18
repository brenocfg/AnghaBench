#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct flexcop_device {int /*<<< orphan*/  (* write_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_2__) ;TYPE_2__ (* read_ibi_reg ) (struct flexcop_device*,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {int reset_block_300; int Block_reset_enable; } ;
struct TYPE_10__ {TYPE_1__ sw_reset_210; int /*<<< orphan*/  raw; } ;
typedef  TYPE_2__ flexcop_ibi_value ;

/* Variables and functions */
 int /*<<< orphan*/  ctrl_208 ; 
 int /*<<< orphan*/  deb_rdump (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ ibi_zero ; 
 TYPE_2__ stub1 (struct flexcop_device*,int /*<<< orphan*/ ) ; 
 TYPE_2__ stub2 (struct flexcop_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  stub4 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  stub5 (struct flexcop_device*,int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  sw_reset_210 ; 

void flexcop_reset_block_300(struct flexcop_device *fc)
{
	flexcop_ibi_value v208_save = fc->read_ibi_reg(fc, ctrl_208),
			  v210 = fc->read_ibi_reg(fc, sw_reset_210);

	deb_rdump("208: %08x, 210: %08x\n", v208_save.raw, v210.raw);
	fc->write_ibi_reg(fc,ctrl_208,ibi_zero);

	v210.sw_reset_210.reset_block_300 = 1;
	v210.sw_reset_210.Block_reset_enable = 0xb2;

	fc->write_ibi_reg(fc,sw_reset_210,v210);
	fc->write_ibi_reg(fc,ctrl_208,v208_save);
}