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
struct MD5Context {int dummy; } ;
struct TYPE_5__ {scalar_t__ offset; scalar_t__ size; } ;
typedef  TYPE_1__ esp_partition_pos_t ;
struct TYPE_6__ {int magic; scalar_t__ type; scalar_t__ subtype; TYPE_1__ pos; } ;
typedef  TYPE_2__ esp_partition_info_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  digest ;
struct TYPE_7__ {scalar_t__ chip_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_SIZE ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int ESP_PARTITION_MAGIC ; 
 int ESP_PARTITION_MAGIC_MD5 ; 
 int ESP_PARTITION_TABLE_MAX_ENTRIES ; 
 int /*<<< orphan*/  MD5Final (unsigned char*,struct MD5Context*) ; 
 int /*<<< orphan*/  MD5Init (struct MD5Context*) ; 
 int /*<<< orphan*/  MD5Update (struct MD5Context*,unsigned char*,int) ; 
 scalar_t__ PART_SUBTYPE_END ; 
 scalar_t__ PART_TYPE_END ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_3__ g_rom_flashchip ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 

esp_err_t esp_partition_table_verify(const esp_partition_info_t *partition_table, bool log_errors, int *num_partitions)
{
    int md5_found = 0;
    int num_parts;
    uint32_t chip_size = g_rom_flashchip.chip_size;
    *num_partitions = 0;

    for (num_parts = 0; num_parts < ESP_PARTITION_TABLE_MAX_ENTRIES; num_parts++) {
        const esp_partition_info_t *part = &partition_table[num_parts];

        if (part->magic == ESP_PARTITION_MAGIC) {
            const esp_partition_pos_t *pos = &part->pos;
            if (pos->offset > chip_size || pos->offset + pos->size > chip_size) {
                if (log_errors) {
                    ESP_LOGE(TAG, "partition %d invalid - offset 0x%x size 0x%x exceeds flash chip size 0x%x",
                             num_parts, pos->offset, pos->size, chip_size);
                }
                return ESP_ERR_INVALID_SIZE;
            }
        } else if (part->magic == ESP_PARTITION_MAGIC_MD5) {
            if (md5_found) {
                if (log_errors) {
                    ESP_LOGE(TAG, "Only one MD5 checksum is allowed");
                }
                return ESP_ERR_INVALID_STATE;
            }

            struct MD5Context context;
            unsigned char digest[16];
            MD5Init(&context);
            MD5Update(&context, (unsigned char *) partition_table, num_parts * sizeof(esp_partition_info_t));
            MD5Final(digest, &context);

            unsigned char *md5sum = ((unsigned char *) part) + 16; // skip the 2B magic number and the 14B fillup bytes

            if (memcmp(md5sum, digest, sizeof(digest)) != 0) {
                if (log_errors) {
                    ESP_LOGE(TAG, "Incorrect MD5 checksum");
                }
                return ESP_ERR_INVALID_STATE;
            }
            //MD5 checksum matches and we continue with the next interation in
            //order to detect the end of the partition table
            md5_found = 1;
        } else if (part->magic == 0xFFFF
                   && part->type == PART_TYPE_END
                   && part->subtype == PART_SUBTYPE_END) {
            ESP_LOGD(TAG, "partition table verified, %d entries", num_parts);
            *num_partitions = num_parts - md5_found; //do not count the partition where the MD5 checksum is held
            return ESP_OK;
        } else {
            if (log_errors) {
                ESP_LOGE(TAG, "partition %d invalid magic number 0x%x", num_parts, part->magic);
            }
            return ESP_ERR_INVALID_STATE;
        }
    }

    if (log_errors) {
        ESP_LOGE(TAG, "partition table has no terminating entry, not valid");
    }
    return ESP_ERR_INVALID_STATE;
}