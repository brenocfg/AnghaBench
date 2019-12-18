#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  esp_himem_rangehandle_t ;
typedef  int /*<<< orphan*/  esp_himem_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int ESP_HIMEM_BLKSZ ; 
 int /*<<< orphan*/  check_mem_seed (int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  esp_himem_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_himem_alloc_map_range (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_himem_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_himem_free_map_range (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_himem_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  esp_himem_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fill_mem_seed (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static bool test_region(int check_size, int seed)
{
    esp_himem_handle_t mh; //Handle for the address space we're using
    esp_himem_rangehandle_t rh; //Handle for the actual RAM.
    bool ret = true;

    //Allocate the memory we're going to check.
    ESP_ERROR_CHECK(esp_himem_alloc(check_size, &mh));
    //Allocate a block of address range
    ESP_ERROR_CHECK(esp_himem_alloc_map_range(ESP_HIMEM_BLKSZ, &rh));
    for (int i = 0; i < check_size; i += ESP_HIMEM_BLKSZ) {
        uint32_t *ptr = NULL;
        //Map in block, write pseudo-random data, unmap block.
        ESP_ERROR_CHECK(esp_himem_map(mh, rh, i, 0, ESP_HIMEM_BLKSZ, 0, (void**)&ptr));
        fill_mem_seed(i ^ seed, ptr, ESP_HIMEM_BLKSZ); //
        ESP_ERROR_CHECK(esp_himem_unmap(rh, ptr, ESP_HIMEM_BLKSZ));
    }
    vTaskDelay(5); //give the OS some time to do things so the task watchdog doesn't bark
    for (int i = 0; i < check_size; i += ESP_HIMEM_BLKSZ) {
        uint32_t *ptr;
        //Map in block, check against earlier written pseudo-random data, unmap block.
        ESP_ERROR_CHECK(esp_himem_map(mh, rh, i, 0, ESP_HIMEM_BLKSZ, 0, (void**)&ptr));
        if (!check_mem_seed(i ^ seed, ptr, ESP_HIMEM_BLKSZ, i)) {
            printf("Error in block %d\n", i / ESP_HIMEM_BLKSZ);
            ret = false;
        }
        ESP_ERROR_CHECK(esp_himem_unmap(rh, ptr, ESP_HIMEM_BLKSZ));
        if (!ret) break; //don't check rest of blocks if error occurred
    }
    //Okay, all done!
    ESP_ERROR_CHECK(esp_himem_free(mh));
    ESP_ERROR_CHECK(esp_himem_free_map_range(rh));
    return ret;
}