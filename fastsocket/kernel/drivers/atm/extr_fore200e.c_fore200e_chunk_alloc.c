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
struct fore200e {TYPE_1__* bus; } ;
struct chunk {int alloc_size; int align_size; int direction; int /*<<< orphan*/ * align_addr; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/ * alloc_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dma_map ) (struct fore200e*,int /*<<< orphan*/ *,int,int) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long FORE200E_ALIGN (int /*<<< orphan*/ *,int) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/ * kzalloc (int,int) ; 
 int /*<<< orphan*/  stub1 (struct fore200e*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int
fore200e_chunk_alloc(struct fore200e* fore200e, struct chunk* chunk, int size, int alignment, int direction)
{
    unsigned long offset = 0;

    if (alignment <= sizeof(int))
	alignment = 0;

    chunk->alloc_size = size + alignment;
    chunk->align_size = size;
    chunk->direction  = direction;

    chunk->alloc_addr = kzalloc(chunk->alloc_size, GFP_KERNEL | GFP_DMA);
    if (chunk->alloc_addr == NULL)
	return -ENOMEM;

    if (alignment > 0)
	offset = FORE200E_ALIGN(chunk->alloc_addr, alignment); 
    
    chunk->align_addr = chunk->alloc_addr + offset;

    chunk->dma_addr = fore200e->bus->dma_map(fore200e, chunk->align_addr, chunk->align_size, direction);
    
    return 0;
}