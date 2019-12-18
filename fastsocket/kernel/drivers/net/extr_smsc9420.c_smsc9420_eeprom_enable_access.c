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
struct smsc9420_pdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_CFG ; 
 unsigned int GPIO_CFG_EEPR_EN_ ; 
 int /*<<< orphan*/  msleep (int) ; 
 unsigned int smsc9420_reg_read (struct smsc9420_pdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smsc9420_reg_write (struct smsc9420_pdata*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void smsc9420_eeprom_enable_access(struct smsc9420_pdata *pd)
{
	unsigned int temp = smsc9420_reg_read(pd, GPIO_CFG);
	temp &= ~GPIO_CFG_EEPR_EN_;
	smsc9420_reg_write(pd, GPIO_CFG, temp);
	msleep(1);
}