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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct ioat_chan_common {scalar_t__ reg_base; TYPE_1__* device; } ;
struct TYPE_2__ {int /*<<< orphan*/  version; } ;

/* Variables and functions */
 scalar_t__ IOAT_CHANSTS_OFFSET_HIGH (int /*<<< orphan*/ ) ; 
 scalar_t__ IOAT_CHANSTS_OFFSET_LOW (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline u64 ioat_chansts(struct ioat_chan_common *chan)
{
	u8 ver = chan->device->version;
	u64 status;
	u32 status_lo;

	/* We need to read the low address first as this causes the
	 * chipset to latch the upper bits for the subsequent read
	 */
	status_lo = readl(chan->reg_base + IOAT_CHANSTS_OFFSET_LOW(ver));
	status = readl(chan->reg_base + IOAT_CHANSTS_OFFSET_HIGH(ver));
	status <<= 32;
	status |= status_lo;

	return status;
}