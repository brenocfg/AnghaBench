#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  spi_flash_mmap_handle_t ;
struct TYPE_9__ {scalar_t__ type; scalar_t__ subtype; int encrypted; scalar_t__* label; int /*<<< orphan*/  size; int /*<<< orphan*/  address; int /*<<< orphan*/  flash_chip; } ;
struct TYPE_10__ {int user_registered; TYPE_2__ info; } ;
typedef  TYPE_3__ partition_list_item_t ;
struct TYPE_8__ {int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct TYPE_11__ {scalar_t__ magic; scalar_t__ type; scalar_t__ subtype; int flags; scalar_t__ label; TYPE_1__ pos; } ;
typedef  TYPE_4__ esp_partition_info_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ ESP_PARTITION_MAGIC ; 
 int ESP_PARTITION_TABLE_OFFSET ; 
 int PART_FLAG_ENCRYPTED ; 
 scalar_t__ PART_SUBTYPE_DATA_NVS_KEYS ; 
 scalar_t__ PART_SUBTYPE_DATA_OTA ; 
 scalar_t__ PART_TYPE_APP ; 
 scalar_t__ PART_TYPE_DATA ; 
 int /*<<< orphan*/  SLIST_INSERT_AFTER (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_FLASH_MMAP_DATA ; 
 int SPI_FLASH_SEC_SIZE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  esp_flash_default_chip ; 
 int /*<<< orphan*/  esp_flash_encryption_enabled () ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  s_partition_list ; 
 scalar_t__ spi_flash_mmap (int,int,int /*<<< orphan*/ ,void const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_flash_munmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (scalar_t__*,char const*,int) ; 

__attribute__((used)) static esp_err_t load_partitions(void)
{
    const uint32_t* ptr;
    spi_flash_mmap_handle_t handle;
    // map 64kB block where partition table is located
    esp_err_t err = spi_flash_mmap(ESP_PARTITION_TABLE_OFFSET & 0xffff0000,
            SPI_FLASH_SEC_SIZE, SPI_FLASH_MMAP_DATA, (const void**) &ptr, &handle);
    if (err != ESP_OK) {
        return err;
    }
    // calculate partition address within mmap-ed region
    const esp_partition_info_t* it = (const esp_partition_info_t*)
            (ptr + (ESP_PARTITION_TABLE_OFFSET & 0xffff) / sizeof(*ptr));
    const esp_partition_info_t* end = it + SPI_FLASH_SEC_SIZE / sizeof(*it);
    // tail of the linked list of partitions
    partition_list_item_t* last = NULL;
    for (; it != end; ++it) {
        if (it->magic != ESP_PARTITION_MAGIC) {
            break;
        }
        // allocate new linked list item and populate it with data from partition table
        partition_list_item_t* item = (partition_list_item_t*) calloc(sizeof(partition_list_item_t), 1);
        if (item == NULL) {
            err = ESP_ERR_NO_MEM;
            break;
        }
        item->info.flash_chip = esp_flash_default_chip;
        item->info.address = it->pos.offset;
        item->info.size = it->pos.size;
        item->info.type = it->type;
        item->info.subtype = it->subtype;
        item->info.encrypted = it->flags & PART_FLAG_ENCRYPTED;
        item->user_registered = false;

        if (!esp_flash_encryption_enabled()) {
            /* If flash encryption is not turned on, no partitions should be treated as encrypted */
            item->info.encrypted = false;
        } else if (it->type == PART_TYPE_APP
                || (it->type == PART_TYPE_DATA && it->subtype == PART_SUBTYPE_DATA_OTA)
                || (it->type == PART_TYPE_DATA && it->subtype == PART_SUBTYPE_DATA_NVS_KEYS)) {
            /* If encryption is turned on, all app partitions and OTA data
               are always encrypted */
            item->info.encrypted = true;
        }

        // it->label may not be zero-terminated
        strncpy(item->info.label, (const char*) it->label, sizeof(item->info.label) - 1);
        item->info.label[sizeof(it->label)] = 0;
        // add it to the list
        if (last == NULL) {
            SLIST_INSERT_HEAD(&s_partition_list, item, next);
        } else {
            SLIST_INSERT_AFTER(last, item, next);
        }
        last = item;
    }
    spi_flash_munmap(handle);
    return err;
}