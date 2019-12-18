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

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 

__attribute__((used)) static inline unsigned ni_stc_dma_channel_select_bitfield(unsigned channel)
{
	if (channel < 4)
		return 1 << channel;
	if (channel == 4)
		return 0x3;
	if (channel == 5)
		return 0x5;
	BUG();
	return 0;
}