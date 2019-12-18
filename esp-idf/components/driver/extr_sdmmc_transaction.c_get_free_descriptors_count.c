#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * next_desc_ptr; scalar_t__ owned_by_idmac; } ;
typedef  TYPE_1__ sdmmc_desc_t ;
struct TYPE_5__ {size_t next_desc; } ;

/* Variables and functions */
 size_t SDMMC_DMA_DESC_CNT ; 
 TYPE_3__ s_cur_transfer ; 
 TYPE_1__* s_dma_desc ; 

__attribute__((used)) static size_t get_free_descriptors_count(void)
{
    const size_t next = s_cur_transfer.next_desc;
    size_t count = 0;
    /* Starting with the current DMA descriptor, count the number of
     * descriptors which have 'owned_by_idmac' set to 0. These are the
     * descriptors already processed by the DMA engine.
     */
    for (size_t i = 0; i < SDMMC_DMA_DESC_CNT; ++i) {
        sdmmc_desc_t* desc = &s_dma_desc[(next + i) % SDMMC_DMA_DESC_CNT];
        if (desc->owned_by_idmac) {
            break;
        }
        ++count;
        if (desc->next_desc_ptr == NULL) {
            /* final descriptor in the chain */
            break;
        }
    }
    return count;
}