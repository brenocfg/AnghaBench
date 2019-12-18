#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* esp_himem_rangehandle_t ;
typedef  TYPE_2__* esp_himem_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_10__ {int is_mapped; } ;
struct TYPE_9__ {int is_mapped; size_t ram_block; } ;
struct TYPE_8__ {int block_ct; size_t* block; } ;
struct TYPE_7__ {int block_ct; int block_start; } ;

/* Variables and functions */
 size_t CACHE_BLOCKSIZE ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_SIZE ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  HIMEM_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 size_t PHYS_HIMEM_BLOCKSTART ; 
 scalar_t__ VIRT_HIMEM_RANGE_BLOCKSTART ; 
 scalar_t__ VIRT_HIMEM_RANGE_START ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ramblock_idx_valid (size_t) ; 
 TYPE_4__* s_ram_descriptor ; 
 TYPE_3__* s_range_descriptor ; 
 int /*<<< orphan*/  set_bank (scalar_t__,size_t,int) ; 
 int /*<<< orphan*/  spinlock ; 

esp_err_t esp_himem_map(esp_himem_handle_t handle, esp_himem_rangehandle_t range, size_t ram_offset, size_t range_offset, size_t len, int flags, void **out_ptr)
{
    int ram_block = ram_offset / CACHE_BLOCKSIZE;
    int range_block = range_offset / CACHE_BLOCKSIZE;
    int blockcount = len / CACHE_BLOCKSIZE;
    HIMEM_CHECK(s_ram_descriptor == NULL, "Himem not available!", ESP_ERR_INVALID_STATE);
    //Offsets and length must be block-aligned
    HIMEM_CHECK(ram_offset % CACHE_BLOCKSIZE != 0, "ram offset not aligned to blocksize", ESP_ERR_INVALID_ARG);
    HIMEM_CHECK(range_offset % CACHE_BLOCKSIZE != 0, "range not aligned to blocksize", ESP_ERR_INVALID_ARG);
    HIMEM_CHECK(len % CACHE_BLOCKSIZE != 0, "length not aligned to blocksize", ESP_ERR_INVALID_ARG);
    //ram and range should be within allocated range
    HIMEM_CHECK(ram_block + blockcount > handle->block_ct, "args not in range of phys ram handle", ESP_ERR_INVALID_SIZE);
    HIMEM_CHECK(range_block + blockcount > range->block_ct, "args not in range of range handle", ESP_ERR_INVALID_SIZE);

    //Check if ram blocks aren't already mapped, and if memory range is unmapped
    for (int i = 0; i < blockcount; i++) {
        HIMEM_CHECK(s_ram_descriptor[handle->block[i + ram_block]].is_mapped, "ram already mapped", ESP_ERR_INVALID_STATE);
        HIMEM_CHECK(s_range_descriptor[range->block_start + i + range_block].is_mapped, "range already mapped", ESP_ERR_INVALID_STATE);
    }

    //Map and mark as mapped
    portENTER_CRITICAL(&spinlock);
    for (int i = 0; i < blockcount; i++) {
        assert(ramblock_idx_valid(handle->block[i + ram_block]));
        s_ram_descriptor[handle->block[i + ram_block]].is_mapped = 1;
        s_range_descriptor[range->block_start + i + range_block].is_mapped = 1;
        s_range_descriptor[range->block_start + i + range_block].ram_block = handle->block[i + ram_block];
    }
    portEXIT_CRITICAL(&spinlock);
    for (int i = 0; i < blockcount; i++) {
        set_bank(VIRT_HIMEM_RANGE_BLOCKSTART + range->block_start + i + range_block, handle->block[i + ram_block] + PHYS_HIMEM_BLOCKSTART, 1);
    }

    //Set out pointer
    *out_ptr = (void *)(VIRT_HIMEM_RANGE_START + (range->block_start + range_offset) * CACHE_BLOCKSIZE);
    return ESP_OK;
}