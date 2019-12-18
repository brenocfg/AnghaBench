#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct TYPE_9__ {intptr_t type; intptr_t subtype; TYPE_1__ pos; int /*<<< orphan*/  label; } ;
typedef  TYPE_2__ esp_partition_info_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_10__ {TYPE_1__ ota_info; int /*<<< orphan*/  app_count; TYPE_1__* ota; TYPE_1__ test; TYPE_1__ factory; } ;
typedef  TYPE_3__ bootloader_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,intptr_t,...) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  ESP_PARTITION_TABLE_MAX_LEN ; 
 intptr_t ESP_PARTITION_TABLE_OFFSET ; 
#define  PART_SUBTYPE_DATA_EFUSE_EM 136 
#define  PART_SUBTYPE_DATA_NVS_KEYS 135 
#define  PART_SUBTYPE_DATA_OTA 134 
#define  PART_SUBTYPE_DATA_RF 133 
#define  PART_SUBTYPE_DATA_WIFI 132 
#define  PART_SUBTYPE_FACTORY 131 
 size_t PART_SUBTYPE_OTA_FLAG ; 
 size_t PART_SUBTYPE_OTA_MASK ; 
#define  PART_SUBTYPE_TEST 130 
#define  PART_TYPE_APP 129 
#define  PART_TYPE_DATA 128 
 int /*<<< orphan*/  TAG ; 
 TYPE_2__* bootloader_mmap (intptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bootloader_munmap (TYPE_2__ const*) ; 
 int /*<<< orphan*/  esp_efuse_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_partition_table_verify (TYPE_2__ const*,int,int*) ; 

bool bootloader_utility_load_partition_table(bootloader_state_t *bs)
{
    const esp_partition_info_t *partitions;
    const char *partition_usage;
    esp_err_t err;
    int num_partitions;

    partitions = bootloader_mmap(ESP_PARTITION_TABLE_OFFSET, ESP_PARTITION_TABLE_MAX_LEN);
    if (!partitions) {
        ESP_LOGE(TAG, "bootloader_mmap(0x%x, 0x%x) failed", ESP_PARTITION_TABLE_OFFSET, ESP_PARTITION_TABLE_MAX_LEN);
        return false;
    }
    ESP_LOGD(TAG, "mapped partition table 0x%x at 0x%x", ESP_PARTITION_TABLE_OFFSET, (intptr_t)partitions);

    err = esp_partition_table_verify(partitions, true, &num_partitions);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to verify partition table");
        return false;
    }

    ESP_LOGI(TAG, "Partition Table:");
    ESP_LOGI(TAG, "## Label            Usage          Type ST Offset   Length");

    for (int i = 0; i < num_partitions; i++) {
        const esp_partition_info_t *partition = &partitions[i];
        ESP_LOGD(TAG, "load partition table entry 0x%x", (intptr_t)partition);
        ESP_LOGD(TAG, "type=%x subtype=%x", partition->type, partition->subtype);
        partition_usage = "unknown";

        /* valid partition table */
        switch (partition->type) {
        case PART_TYPE_APP: /* app partition */
            switch (partition->subtype) {
            case PART_SUBTYPE_FACTORY: /* factory binary */
                bs->factory = partition->pos;
                partition_usage = "factory app";
                break;
            case PART_SUBTYPE_TEST: /* test binary */
                bs->test = partition->pos;
                partition_usage = "test app";
                break;
            default:
                /* OTA binary */
                if ((partition->subtype & ~PART_SUBTYPE_OTA_MASK) == PART_SUBTYPE_OTA_FLAG) {
                    bs->ota[partition->subtype & PART_SUBTYPE_OTA_MASK] = partition->pos;
                    ++bs->app_count;
                    partition_usage = "OTA app";
                } else {
                    partition_usage = "Unknown app";
                }
                break;
            }
            break; /* PART_TYPE_APP */
        case PART_TYPE_DATA: /* data partition */
            switch (partition->subtype) {
            case PART_SUBTYPE_DATA_OTA: /* ota data */
                bs->ota_info = partition->pos;
                partition_usage = "OTA data";
                break;
            case PART_SUBTYPE_DATA_RF:
                partition_usage = "RF data";
                break;
            case PART_SUBTYPE_DATA_WIFI:
                partition_usage = "WiFi data";
                break;
            case PART_SUBTYPE_DATA_NVS_KEYS:
                partition_usage = "NVS keys";
                break;
            case PART_SUBTYPE_DATA_EFUSE_EM:
                partition_usage = "efuse";
#ifdef CONFIG_BOOTLOADER_EFUSE_SECURE_VERSION_EMULATE
                esp_efuse_init(partition->pos.offset, partition->pos.size);
#endif
                break;
            default:
                partition_usage = "Unknown data";
                break;
            }
            break; /* PARTITION_USAGE_DATA */
        default: /* other partition type */
            break;
        }

        /* print partition type info */
        ESP_LOGI(TAG, "%2d %-16s %-16s %02x %02x %08x %08x", i, partition->label, partition_usage,
                 partition->type, partition->subtype,
                 partition->pos.offset, partition->pos.size);
    }

    bootloader_munmap(partitions);

    ESP_LOGI(TAG, "End of partition table");
    return true;
}