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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct fw_card {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ CSR_CHANNELS_AVAILABLE_HI ; 
 scalar_t__ CSR_CHANNELS_AVAILABLE_LO ; 
 scalar_t__ CSR_REGISTER_BASE ; 
 int /*<<< orphan*/  manage_channel (struct fw_card*,int,int,int,scalar_t__,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void deallocate_channel(struct fw_card *card, int irm_id,
			       int generation, int channel, __be32 buffer[2])
{
	u32 mask;
	u64 offset;

	mask = channel < 32 ? 1 << channel : 1 << (channel - 32);
	offset = channel < 32 ? CSR_REGISTER_BASE + CSR_CHANNELS_AVAILABLE_HI :
				CSR_REGISTER_BASE + CSR_CHANNELS_AVAILABLE_LO;

	manage_channel(card, irm_id, generation, mask, offset, false, buffer);
}