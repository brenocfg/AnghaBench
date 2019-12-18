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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  DMA_MemMap_t ;

/* Variables and functions */
 int dma_map_add_region (int /*<<< orphan*/ *,void*,size_t) ; 
 int dma_map_start (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dma_unmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int dma_map_mem(DMA_MemMap_t *memMap,	/* Stores state information about the map */
		void *mem,	/* Virtual address that we want to get a map of */
		size_t numBytes,	/* Number of bytes being mapped */
		enum dma_data_direction dir	/* Direction that the mapping will be going */
    ) {
	int rc;

	rc = dma_map_start(memMap, dir);
	if (rc == 0) {
		rc = dma_map_add_region(memMap, mem, numBytes);
		if (rc < 0) {
			/* Since the add fails, this function will fail, and the caller won't */
			/* call unmap, so we need to do it here. */

			dma_unmap(memMap, 0);
		}
	}

	return rc;
}