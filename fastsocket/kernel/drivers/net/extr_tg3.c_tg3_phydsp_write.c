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
 int /*<<< orphan*/  MII_TG3_DSP_ADDRESS ; 
 int /*<<< orphan*/  MII_TG3_DSP_RW_PORT ; 
 int tg3_writephy (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tg3_phydsp_write(struct tg3 *tp, u32 reg, u32 val)
{
	int err;

	err = tg3_writephy(tp, MII_TG3_DSP_ADDRESS, reg);
	if (!err)
		err = tg3_writephy(tp, MII_TG3_DSP_RW_PORT, val);

	return err;
}