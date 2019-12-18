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
struct rc_dev {struct ene_device* priv; } ;
struct ene_device {int tx_period; } ;

/* Variables and functions */
 int ENE_CIRMOD_PRD_MAX ; 
 int ENE_CIRMOD_PRD_MIN ; 
 int /*<<< orphan*/  dbg (char*,int,...) ; 
 int /*<<< orphan*/  ene_tx_set_carrier (struct ene_device*) ; 

__attribute__((used)) static int ene_set_tx_carrier(struct rc_dev *rdev, u32 carrier)
{
	struct ene_device *dev = rdev->priv;
	u32 period = 2000000 / carrier;

	dbg("TX: attempt to set tx carrier to %d kHz", carrier);

	if (period && (period > ENE_CIRMOD_PRD_MAX ||
			period < ENE_CIRMOD_PRD_MIN)) {

		dbg("TX: out of range %d-%d kHz carrier",
			2000 / ENE_CIRMOD_PRD_MIN, 2000 / ENE_CIRMOD_PRD_MAX);
		return -1;
	}

	dev->tx_period = period;
	ene_tx_set_carrier(dev);
	return 0;
}