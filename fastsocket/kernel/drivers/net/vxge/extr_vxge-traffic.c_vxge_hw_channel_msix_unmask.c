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
typedef  int /*<<< orphan*/  u32 ;
struct __vxge_hw_channel {TYPE_1__* common_reg; } ;
struct TYPE_2__ {int /*<<< orphan*/ * clear_msix_mask_vect; } ;

/* Variables and functions */
 int /*<<< orphan*/  __vxge_hw_pio_mem_write32_upper (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vxge_bVALn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vxge_mBIT (int) ; 

void
vxge_hw_channel_msix_unmask(struct __vxge_hw_channel *channel, int msix_id)
{

	__vxge_hw_pio_mem_write32_upper(
		(u32)vxge_bVALn(vxge_mBIT(msix_id >> 2), 0, 32),
		&channel->common_reg->clear_msix_mask_vect[msix_id%4]);

	return;
}