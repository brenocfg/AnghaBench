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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_2__ {int /*<<< orphan*/ * block_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MALLOC_CAP_DMA ; 
 int /*<<< orphan*/  SDSPI_BLOCK_BUF_SIZE ; 
 int /*<<< orphan*/ * heap_caps_malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* s_slots ; 

__attribute__((used)) static esp_err_t get_block_buf(int slot, uint8_t** out_buf)
{
    if (s_slots[slot].block_buf == NULL) {
        s_slots[slot].block_buf = heap_caps_malloc(SDSPI_BLOCK_BUF_SIZE, MALLOC_CAP_DMA);
        if (s_slots[slot].block_buf == NULL) {
            return ESP_ERR_NO_MEM;
        }
    }
    *out_buf = s_slots[slot].block_buf;
    return ESP_OK;
}