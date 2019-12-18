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
 int /*<<< orphan*/  DMA_MAP_FREE ; 
 int /*<<< orphan*/ * dma_alloc_map ; 
 int request_dma (int,char*) ; 

int sound_alloc_dma(int chn, char *deviceID)
{
	int err;

	if ((err = request_dma(chn, deviceID)) != 0)
		return err;

	dma_alloc_map[chn] = DMA_MAP_FREE;

	return 0;
}