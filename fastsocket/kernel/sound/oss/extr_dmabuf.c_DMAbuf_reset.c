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
struct TYPE_2__ {int open_mode; } ;

/* Variables and functions */
 int OPEN_READ ; 
 int OPEN_WRITE ; 
 TYPE_1__** audio_devs ; 
 int /*<<< orphan*/  dma_reset_input (int) ; 
 int /*<<< orphan*/  dma_reset_output (int) ; 

void DMAbuf_reset(int dev)
{
	if (audio_devs[dev]->open_mode & OPEN_WRITE)
		dma_reset_output(dev);

	if (audio_devs[dev]->open_mode & OPEN_READ)
		dma_reset_input(dev);
}