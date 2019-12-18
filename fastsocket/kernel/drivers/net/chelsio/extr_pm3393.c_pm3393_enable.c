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
typedef  int u32 ;
struct cmac {TYPE_1__* instance; } ;
struct TYPE_2__ {int fc; int enabled; } ;

/* Variables and functions */
 int MAC_DIRECTION_RX ; 
 int MAC_DIRECTION_TX ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int RXXG_CONF1_VAL ; 
 int SUNI1x10GEXP_BITMSK_RXXG_RXEN ; 
 int SUNI1x10GEXP_BITMSK_TXXG_FCRX ; 
 int SUNI1x10GEXP_BITMSK_TXXG_FCTX ; 
 int SUNI1x10GEXP_BITMSK_TXXG_TXEN0 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXXG_CONFIG_1 ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_TXXG_CONFIG_1 ; 
 int TXXG_CONF1_VAL ; 
 int /*<<< orphan*/  pmwrite (struct cmac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pm3393_enable(struct cmac *cmac, int which)
{
	if (which & MAC_DIRECTION_RX)
		pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_CONFIG_1,
			(RXXG_CONF1_VAL | SUNI1x10GEXP_BITMSK_RXXG_RXEN));

	if (which & MAC_DIRECTION_TX) {
		u32 val = TXXG_CONF1_VAL | SUNI1x10GEXP_BITMSK_TXXG_TXEN0;

		if (cmac->instance->fc & PAUSE_RX)
			val |= SUNI1x10GEXP_BITMSK_TXXG_FCRX;
		if (cmac->instance->fc & PAUSE_TX)
			val |= SUNI1x10GEXP_BITMSK_TXXG_FCTX;
		pmwrite(cmac, SUNI1x10GEXP_REG_TXXG_CONFIG_1, val);
	}

	cmac->instance->enabled |= which;
	return 0;
}