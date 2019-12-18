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
struct cmac {TYPE_1__* instance; } ;
struct TYPE_2__ {int enabled; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAC_DIRECTION_RX ; 
 int MAC_DIRECTION_TX ; 
 int MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_RXXG_MAX_FRAME_LENGTH ; 
 int /*<<< orphan*/  SUNI1x10GEXP_REG_TXXG_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  pm3393_disable (struct cmac*,int) ; 
 int /*<<< orphan*/  pm3393_enable (struct cmac*,int) ; 
 int /*<<< orphan*/  pmwrite (struct cmac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pm3393_set_mtu(struct cmac *cmac, int mtu)
{
	int enabled = cmac->instance->enabled;

	/* MAX_FRAME_SIZE includes header + FCS, mtu doesn't */
	mtu += 14 + 4;
	if (mtu > MAX_FRAME_SIZE)
		return -EINVAL;

	/* Disable Rx/Tx MAC before configuring it. */
	if (enabled)
		pm3393_disable(cmac, MAC_DIRECTION_RX | MAC_DIRECTION_TX);

	pmwrite(cmac, SUNI1x10GEXP_REG_RXXG_MAX_FRAME_LENGTH, mtu);
	pmwrite(cmac, SUNI1x10GEXP_REG_TXXG_MAX_FRAME_SIZE, mtu);

	if (enabled)
		pm3393_enable(cmac, enabled);
	return 0;
}