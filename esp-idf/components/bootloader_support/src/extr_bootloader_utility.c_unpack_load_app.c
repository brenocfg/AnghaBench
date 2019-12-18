#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ load_addr; scalar_t__ data_len; } ;
typedef  TYPE_2__ esp_image_segment_header_t ;
struct TYPE_5__ {int segment_count; int /*<<< orphan*/  entry_addr; } ;
struct TYPE_7__ {scalar_t__* segment_data; TYPE_1__ image; TYPE_2__* segments; } ;
typedef  TYPE_3__ esp_image_metadata_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAP_ERR_MSG ; 
 scalar_t__ SOC_DROM_HIGH ; 
 scalar_t__ SOC_DROM_LOW ; 
 scalar_t__ SOC_IROM_HIGH ; 
 scalar_t__ SOC_IROM_LOW ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  set_cache_and_start_app (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unpack_load_app(const esp_image_metadata_t *data)
{
    uint32_t drom_addr = 0;
    uint32_t drom_load_addr = 0;
    uint32_t drom_size = 0;
    uint32_t irom_addr = 0;
    uint32_t irom_load_addr = 0;
    uint32_t irom_size = 0;

    // Find DROM & IROM addresses, to configure cache mappings
    for (int i = 0; i < data->image.segment_count; i++) {
        const esp_image_segment_header_t *header = &data->segments[i];
        if (header->load_addr >= SOC_DROM_LOW && header->load_addr < SOC_DROM_HIGH) {
            if (drom_addr != 0) {
                ESP_LOGE(TAG, MAP_ERR_MSG, "DROM");
            } else {
                ESP_LOGD(TAG, "Mapping segment %d as %s", i, "DROM");
            }
            drom_addr = data->segment_data[i];
            drom_load_addr = header->load_addr;
            drom_size = header->data_len;
        }
        if (header->load_addr >= SOC_IROM_LOW && header->load_addr < SOC_IROM_HIGH) {
            if (irom_addr != 0) {
                ESP_LOGE(TAG, MAP_ERR_MSG, "IROM");
            } else {
                ESP_LOGD(TAG, "Mapping segment %d as %s", i, "IROM");
            }
            irom_addr = data->segment_data[i];
            irom_load_addr = header->load_addr;
            irom_size = header->data_len;
        }
    }

    ESP_LOGD(TAG, "calling set_cache_and_start_app");
    set_cache_and_start_app(drom_addr,
                            drom_load_addr,
                            drom_size,
                            irom_addr,
                            irom_load_addr,
                            irom_size,
                            data->image.entry_addr);
}