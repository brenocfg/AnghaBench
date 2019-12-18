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
struct TYPE_4__ {int owned_by_idmac; int last_descriptor; int second_address_chained; size_t buffer1_ptr; size_t buffer1_size; struct TYPE_4__* next_desc_ptr; } ;
typedef  TYPE_1__ sdmmc_desc_t ;
struct TYPE_5__ {size_t size_remaining; size_t next_desc; size_t ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,size_t,size_t const,size_t,int,int,size_t) ; 
 size_t const SDMMC_DMA_DESC_CNT ; 
 size_t SDMMC_DMA_MAX_BUF_LEN ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ s_cur_transfer ; 
 TYPE_1__* s_dma_desc ; 

__attribute__((used)) static void fill_dma_descriptors(size_t num_desc)
{
    for (size_t i = 0; i < num_desc; ++i) {
        if (s_cur_transfer.size_remaining == 0) {
            return;
        }
        const size_t next = s_cur_transfer.next_desc;
        sdmmc_desc_t* desc = &s_dma_desc[next];
        assert(!desc->owned_by_idmac);
        size_t size_to_fill =
            (s_cur_transfer.size_remaining < SDMMC_DMA_MAX_BUF_LEN) ?
                s_cur_transfer.size_remaining : SDMMC_DMA_MAX_BUF_LEN;
        bool last = size_to_fill == s_cur_transfer.size_remaining;
        desc->last_descriptor = last;
        desc->second_address_chained = 1;
        desc->owned_by_idmac = 1;
        desc->buffer1_ptr = s_cur_transfer.ptr;
        desc->next_desc_ptr = (last) ? NULL : &s_dma_desc[(next + 1) % SDMMC_DMA_DESC_CNT];
        assert(size_to_fill < 4 || size_to_fill % 4 == 0);
        desc->buffer1_size = (size_to_fill + 3) & (~3);

        s_cur_transfer.size_remaining -= size_to_fill;
        s_cur_transfer.ptr += size_to_fill;
        s_cur_transfer.next_desc = (s_cur_transfer.next_desc + 1) % SDMMC_DMA_DESC_CNT;
        ESP_LOGV(TAG, "fill %d desc=%d rem=%d next=%d last=%d sz=%d",
                num_desc, next, s_cur_transfer.size_remaining,
                s_cur_transfer.next_desc, desc->last_descriptor, desc->buffer1_size);
    }
}