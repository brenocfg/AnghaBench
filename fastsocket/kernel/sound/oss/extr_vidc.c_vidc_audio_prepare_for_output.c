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
struct audio_operations {TYPE_1__* dmap_out; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NODMA ; 
 struct audio_operations** audio_devs ; 
 int /*<<< orphan*/ * dma_interrupt ; 

__attribute__((used)) static int vidc_audio_prepare_for_output(int dev, int bsize, int bcount)
{
	struct audio_operations *adev = audio_devs[dev];

	dma_interrupt = NULL;
	adev->dmap_out->flags |= DMA_NODMA;

	return 0;
}