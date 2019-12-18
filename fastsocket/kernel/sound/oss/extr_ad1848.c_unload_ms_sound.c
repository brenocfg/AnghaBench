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
struct address_info {scalar_t__ io_base; int /*<<< orphan*/ * slots; int /*<<< orphan*/  dma2; int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad1848_unload (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  sound_unload_audiodev (int /*<<< orphan*/ ) ; 

void unload_ms_sound(struct address_info *hw_config)
{
	ad1848_unload(hw_config->io_base + 4,
		      hw_config->irq,
		      hw_config->dma,
		      hw_config->dma2, 0);
	sound_unload_audiodev(hw_config->slots[0]);
	release_region(hw_config->io_base, 4);
}