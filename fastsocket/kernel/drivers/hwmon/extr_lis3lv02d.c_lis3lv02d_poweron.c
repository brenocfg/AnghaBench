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
typedef  int /*<<< orphan*/  u8 ;
struct lis3lv02d {scalar_t__ whoami; int /*<<< orphan*/  (* write ) (struct lis3lv02d*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read ) (struct lis3lv02d*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* init ) (struct lis3lv02d*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL2_BDU ; 
 int /*<<< orphan*/  CTRL_REG2 ; 
 scalar_t__ LIS_DOUBLE_ID ; 
 int /*<<< orphan*/  stub1 (struct lis3lv02d*) ; 
 int /*<<< orphan*/  stub2 (struct lis3lv02d*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct lis3lv02d*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lis3lv02d_poweron(struct lis3lv02d *lis3)
{
	u8 reg;

	lis3->init(lis3);

	/*
	 * Common configuration
	 * BDU: (12 bits sensors only) LSB and MSB values are not updated until
	 *      both have been read. So the value read will always be correct.
	 */
	if (lis3->whoami == LIS_DOUBLE_ID) {
		lis3->read(lis3, CTRL_REG2, &reg);
		reg |= CTRL2_BDU;
		lis3->write(lis3, CTRL_REG2, reg);
	}
}