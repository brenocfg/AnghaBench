#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spi_flash_mmap_handle_t ;
struct TYPE_8__ {int format_if_mount_failed; size_t max_files; } ;
typedef  TYPE_1__ esp_vfs_fat_sdmmc_mount_config_t ;
struct TYPE_9__ {int size; } ;
typedef  TYPE_2__ esp_partition_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPI_FLASH_MMAP_DATA ; 
 scalar_t__ SPI_FLASH_SEC_SIZE ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_partition_erase_range (TYPE_2__ const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  esp_partition_mmap (TYPE_2__ const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_partition_write (TYPE_2__ const*,int,char const*,scalar_t__) ; 
 int /*<<< orphan*/  esp_vfs_fat_rawflash_mount (char*,char*,TYPE_1__*) ; 
 TYPE_2__* get_test_data_partition () ; 
 scalar_t__ memcmp (char const*,void const*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  spi_flash_munmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_setup(size_t max_files)
{
    extern const char fatfs_start[] asm("_binary_fatfs_img_start");
    extern const char fatfs_end[]   asm("_binary_fatfs_img_end");
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = max_files
    };
    const esp_partition_t* part = get_test_data_partition();

    TEST_ASSERT(part->size == (fatfs_end - fatfs_start - 1));

    spi_flash_mmap_handle_t mmap_handle;
    const void* mmap_ptr;
    TEST_ESP_OK(esp_partition_mmap(part, 0, part->size, SPI_FLASH_MMAP_DATA, &mmap_ptr, &mmap_handle));
    bool content_valid = memcmp(fatfs_start, mmap_ptr, part->size) == 0;
    spi_flash_munmap(mmap_handle);

    if (!content_valid) {
        printf("Copying fatfs.img into test partition...\n");
        esp_partition_erase_range(part, 0, part->size);
        for (int i = 0; i < part->size; i+= SPI_FLASH_SEC_SIZE) {
            ESP_ERROR_CHECK( esp_partition_write(part, i, fatfs_start + i, SPI_FLASH_SEC_SIZE) );
        }
    }

    TEST_ESP_OK(esp_vfs_fat_rawflash_mount("/spiflash", "flash_test", &mount_config));
}