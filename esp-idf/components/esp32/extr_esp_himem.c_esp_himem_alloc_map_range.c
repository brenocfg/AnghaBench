#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* esp_himem_rangehandle_t ;
struct TYPE_7__ {int block_ct; int block_start; } ;
typedef  TYPE_1__ esp_himem_rangedata_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_8__ {int is_alloced; } ;

/* Variables and functions */
 size_t CACHE_BLOCKSIZE ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_SIZE ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  HIMEM_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * s_ram_descriptor ; 
 TYPE_3__* s_range_descriptor ; 
 int s_rangeblockcnt ; 
 int /*<<< orphan*/  spinlock ; 

esp_err_t esp_himem_alloc_map_range(size_t size, esp_himem_rangehandle_t *handle_out)
{
    HIMEM_CHECK(s_ram_descriptor == NULL, "Himem not available!", ESP_ERR_INVALID_STATE);
    HIMEM_CHECK(size % CACHE_BLOCKSIZE != 0, "requested size not aligned to blocksize", ESP_ERR_INVALID_SIZE);
    int blocks = size / CACHE_BLOCKSIZE;
    esp_himem_rangedata_t *r = calloc(sizeof(esp_himem_rangedata_t), 1);
    if (!r) {
        return ESP_ERR_NO_MEM;
    }
    r->block_ct = blocks;
    r->block_start = -1;
    int start_free = 0;
    portENTER_CRITICAL(&spinlock);
    for (int i = 0; i < s_rangeblockcnt; i++) {
        if (s_range_descriptor[i].is_alloced) {
            start_free = i + 1; //optimistically assume next block is free...
        } else if (i - start_free == blocks - 1) {
            //We found a span of blocks that's big enough to allocate the requested range in.
            r->block_start = start_free;
            break;
        }
    }

    if (r->block_start == -1) {
        //Couldn't find enough free blocks
        free(r);
        portEXIT_CRITICAL(&spinlock);
        return ESP_ERR_NO_MEM;
    }
    //Range is found. Mark the blocks as in use.
    for (int i = 0; i < blocks; i++) {
        s_range_descriptor[r->block_start + i].is_alloced = 1;
    }
    portEXIT_CRITICAL(&spinlock);
    //All done.
    *handle_out = r;
    return ESP_OK;
}