#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ DMA_MemMap_t ;

/* Variables and functions */
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int dma_term_mem_map(DMA_MemMap_t *memMap)
{
	down(&memMap->lock);	/* Just being paranoid */

	/* Free up any allocated memory */

	up(&memMap->lock);
	memset(memMap, 0, sizeof(*memMap));

	return 0;
}