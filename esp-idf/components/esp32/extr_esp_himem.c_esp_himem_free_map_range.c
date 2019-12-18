#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* esp_himem_rangehandle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_6__ {int is_alloced; int /*<<< orphan*/  is_mapped; } ;
struct TYPE_5__ {int block_ct; int block_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  HIMEM_CHECK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int rangeblock_idx_valid (int) ; 
 TYPE_2__* s_range_descriptor ; 
 int /*<<< orphan*/  spinlock ; 

esp_err_t esp_himem_free_map_range(esp_himem_rangehandle_t handle)
{
    //Check if any of the blocks in the range have a mapping
    for (int i = 0; i < handle->block_ct; i++) {
        assert(rangeblock_idx_valid(handle->block_start + i));
        assert(s_range_descriptor[i + handle->block_start].is_alloced == 1); //should be, if handle is valid
        HIMEM_CHECK(s_range_descriptor[i + handle->block_start].is_mapped, "memory still mapped to range", ESP_ERR_INVALID_ARG);
    }
    //We should be good to free this. Mark blocks as free.
    portENTER_CRITICAL(&spinlock);
    for (int i = 0; i < handle->block_ct; i++) {
        s_range_descriptor[i + handle->block_start].is_alloced = 0;
    }
    portEXIT_CRITICAL(&spinlock);
    free(handle);
    return ESP_OK;
}