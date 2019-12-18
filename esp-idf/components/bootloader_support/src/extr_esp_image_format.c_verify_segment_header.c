#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int data_len; int load_addr; } ;
typedef  TYPE_1__ esp_image_segment_header_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_IMAGE_INVALID ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int SIXTEEN_MB ; 
 int SPI_FLASH_MMU_PAGE_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 int should_map (int) ; 

__attribute__((used)) static esp_err_t verify_segment_header(int index, const esp_image_segment_header_t *segment, uint32_t segment_data_offs, bool silent)
{
    if ((segment->data_len & 3) != 0
            || segment->data_len >= SIXTEEN_MB) {
        if (!silent) {
            ESP_LOGE(TAG, "invalid segment length 0x%x", segment->data_len);
        }
        return ESP_ERR_IMAGE_INVALID;
    }

    uint32_t load_addr = segment->load_addr;
    bool map_segment = should_map(load_addr);

    /* Check that flash cache mapped segment aligns correctly from flash to its mapped address,
       relative to the 64KB page mapping size.
    */
    ESP_LOGV(TAG, "segment %d map_segment %d segment_data_offs 0x%x load_addr 0x%x",
             index, map_segment, segment_data_offs, load_addr);
    if (map_segment
            && ((segment_data_offs % SPI_FLASH_MMU_PAGE_SIZE) != (load_addr % SPI_FLASH_MMU_PAGE_SIZE))) {
        if (!silent) {
            ESP_LOGE(TAG, "Segment %d load address 0x%08x, doesn't match data 0x%08x",
                     index, load_addr, segment_data_offs);
        }
        return ESP_ERR_IMAGE_INVALID;
    }

    return ESP_OK;
}