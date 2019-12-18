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
typedef  int u32 ;
struct tg3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_TG3_MMD_ADDRESS ; 
 int /*<<< orphan*/  MII_TG3_MMD_CTRL ; 
 int MII_TG3_MMD_CTRL_DATA_NOINC ; 
 int tg3_writephy (struct tg3*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tg3_phy_cl45_write(struct tg3 *tp, u32 devad, u32 addr, u32 val)
{
	int err;

	err = tg3_writephy(tp, MII_TG3_MMD_CTRL, devad);
	if (err)
		goto done;

	err = tg3_writephy(tp, MII_TG3_MMD_ADDRESS, addr);
	if (err)
		goto done;

	err = tg3_writephy(tp, MII_TG3_MMD_CTRL,
			   MII_TG3_MMD_CTRL_DATA_NOINC | devad);
	if (err)
		goto done;

	err = tg3_writephy(tp, MII_TG3_MMD_ADDRESS, val);

done:
	return err;
}