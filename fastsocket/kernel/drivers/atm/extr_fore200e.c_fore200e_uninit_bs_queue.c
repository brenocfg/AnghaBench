#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fore200e {TYPE_2__* bus; TYPE_1__** host_bsq; } ;
struct chunk {scalar_t__ alloc_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dma_chunk_free ) (struct fore200e*,struct chunk*) ;} ;
struct TYPE_3__ {struct chunk rbd_block; struct chunk status; } ;

/* Variables and functions */
 int BUFFER_MAGN_NBR ; 
 int BUFFER_SCHEME_NBR ; 
 int /*<<< orphan*/  stub1 (struct fore200e*,struct chunk*) ; 
 int /*<<< orphan*/  stub2 (struct fore200e*,struct chunk*) ; 

__attribute__((used)) static void
fore200e_uninit_bs_queue(struct fore200e* fore200e)
{
    int scheme, magn;
    
    for (scheme = 0; scheme < BUFFER_SCHEME_NBR; scheme++) {
	for (magn = 0; magn < BUFFER_MAGN_NBR; magn++) {

	    struct chunk* status    = &fore200e->host_bsq[ scheme ][ magn ].status;
	    struct chunk* rbd_block = &fore200e->host_bsq[ scheme ][ magn ].rbd_block;
	    
	    if (status->alloc_addr)
		fore200e->bus->dma_chunk_free(fore200e, status);
	    
	    if (rbd_block->alloc_addr)
		fore200e->bus->dma_chunk_free(fore200e, rbd_block);
	}
    }
}