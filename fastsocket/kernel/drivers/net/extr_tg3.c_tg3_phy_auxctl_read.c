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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int MII_TG3_AUXCTL_MISC_RDSEL_SHIFT ; 
 int MII_TG3_AUXCTL_SHDWSEL_MISC ; 
 int /*<<< orphan*/  MII_TG3_AUX_CTRL ; 
 int tg3_readphy (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tg3_writephy (struct tg3*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tg3_phy_auxctl_read(struct tg3 *tp, int reg, u32 *val)
{
	int err;

	err = tg3_writephy(tp, MII_TG3_AUX_CTRL,
			   (reg << MII_TG3_AUXCTL_MISC_RDSEL_SHIFT) |
			   MII_TG3_AUXCTL_SHDWSEL_MISC);
	if (!err)
		err = tg3_readphy(tp, MII_TG3_AUX_CTRL, val);

	return err;
}