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
struct ssb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSB_IDLOW ; 
 int SSB_IDLOW_INITIATOR ; 
 int /*<<< orphan*/  SSB_IMSTATE ; 
 int SSB_IMSTATE_BUSY ; 
 int SSB_IMSTATE_REJECT ; 
 int /*<<< orphan*/  SSB_TMSHIGH ; 
 int SSB_TMSHIGH_BUSY ; 
 int /*<<< orphan*/  SSB_TMSLOW ; 
 int SSB_TMSLOW_CLOCK ; 
 int SSB_TMSLOW_FGC ; 
 int SSB_TMSLOW_RESET ; 
 int /*<<< orphan*/  ssb_flush_tmslow (struct ssb_device*) ; 
 int ssb_read32 (struct ssb_device*,int /*<<< orphan*/ ) ; 
 int ssb_tmslow_reject_bitmask (struct ssb_device*) ; 
 int /*<<< orphan*/  ssb_wait_bits (struct ssb_device*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ssb_write32 (struct ssb_device*,int /*<<< orphan*/ ,int) ; 

void ssb_device_disable(struct ssb_device *dev, u32 core_specific_flags)
{
	u32 reject, val;

	if (ssb_read32(dev, SSB_TMSLOW) & SSB_TMSLOW_RESET)
		return;

	reject = ssb_tmslow_reject_bitmask(dev);

	if (ssb_read32(dev, SSB_TMSLOW) & SSB_TMSLOW_CLOCK) {
		ssb_write32(dev, SSB_TMSLOW, reject | SSB_TMSLOW_CLOCK);
		ssb_wait_bits(dev, SSB_TMSLOW, reject, 1000, 1);
		ssb_wait_bits(dev, SSB_TMSHIGH, SSB_TMSHIGH_BUSY, 1000, 0);

		if (ssb_read32(dev, SSB_IDLOW) & SSB_IDLOW_INITIATOR) {
			val = ssb_read32(dev, SSB_IMSTATE);
			val |= SSB_IMSTATE_REJECT;
			ssb_write32(dev, SSB_IMSTATE, val);
			ssb_wait_bits(dev, SSB_IMSTATE, SSB_IMSTATE_BUSY, 1000,
				      0);
		}

		ssb_write32(dev, SSB_TMSLOW,
			SSB_TMSLOW_FGC | SSB_TMSLOW_CLOCK |
			reject | SSB_TMSLOW_RESET |
			core_specific_flags);
		ssb_flush_tmslow(dev);

		if (ssb_read32(dev, SSB_IDLOW) & SSB_IDLOW_INITIATOR) {
			val = ssb_read32(dev, SSB_IMSTATE);
			val &= ~SSB_IMSTATE_REJECT;
			ssb_write32(dev, SSB_IMSTATE, val);
		}
	}

	ssb_write32(dev, SSB_TMSLOW,
		    reject | SSB_TMSLOW_RESET |
		    core_specific_flags);
	ssb_flush_tmslow(dev);
}