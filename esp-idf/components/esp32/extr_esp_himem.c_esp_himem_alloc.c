#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int block_ct; struct TYPE_6__* block; } ;
typedef  TYPE_1__ esp_himem_ramdata_t ;
typedef  TYPE_1__* esp_himem_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 size_t CACHE_BLOCKSIZE ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_SIZE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int allocate_blocks (int,TYPE_1__*) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spinlock ; 

esp_err_t esp_himem_alloc(size_t size, esp_himem_handle_t *handle_out)
{
    if (size % CACHE_BLOCKSIZE != 0) {
        return ESP_ERR_INVALID_SIZE;
    }
    int blocks = size / CACHE_BLOCKSIZE;
    esp_himem_ramdata_t *r = calloc(sizeof(esp_himem_ramdata_t), 1);
    if (!r) {
        goto nomem;
    }
    r->block = calloc(sizeof(uint16_t), blocks);
    if (!r->block) {
        goto nomem;
    }
    portENTER_CRITICAL(&spinlock);
    int ok = allocate_blocks(blocks, r->block);
    portEXIT_CRITICAL(&spinlock);
    if (!ok) {
        goto nomem;
    }
    r->block_ct = blocks;
    *handle_out = r;
    return ESP_OK;
nomem:
    if (r) {
        free(r->block);
    }
    free(r);
    return ESP_ERR_NO_MEM;
}