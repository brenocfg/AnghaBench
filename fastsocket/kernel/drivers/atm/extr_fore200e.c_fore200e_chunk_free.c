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
struct chunk {int /*<<< orphan*/  alloc_addr; int /*<<< orphan*/  direction; int /*<<< orphan*/  dma_size; int /*<<< orphan*/  dma_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dma_unmap ) (struct fore200e*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct fore200e*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fore200e_chunk_free(struct fore200e* fore200e, struct chunk* chunk)
{
    fore200e->bus->dma_unmap(fore200e, chunk->dma_addr, chunk->dma_size, chunk->direction);

    kfree(chunk->alloc_addr);
}