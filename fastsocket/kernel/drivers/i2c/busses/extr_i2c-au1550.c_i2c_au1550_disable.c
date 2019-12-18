#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_au1550_data {scalar_t__ psc_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  psc_ctrl; scalar_t__ psc_smbcfg; } ;
typedef  TYPE_1__ psc_smb_t ;

/* Variables and functions */
 int /*<<< orphan*/  PSC_CTRL_DISABLE ; 
 int /*<<< orphan*/  au_sync () ; 

__attribute__((used)) static void i2c_au1550_disable(struct i2c_au1550_data *priv)
{
	volatile psc_smb_t *sp = (volatile psc_smb_t *)priv->psc_base;

	sp->psc_smbcfg = 0;
	sp->psc_ctrl = PSC_CTRL_DISABLE;
	au_sync();
}