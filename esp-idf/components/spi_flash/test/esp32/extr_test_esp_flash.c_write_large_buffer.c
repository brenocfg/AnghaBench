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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ address; } ;
typedef  TYPE_1__ esp_partition_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 size_t SPI_FLASH_SEC_SIZE ; 
 int /*<<< orphan*/  esp_flash_erase_region (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  esp_flash_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void write_large_buffer(esp_flash_t *chip, const esp_partition_t *part, const uint8_t *source, size_t length)
{
    printf("Writing chip %p, %d bytes from source %p\n", chip, length, source);

    ESP_ERROR_CHECK( esp_flash_erase_region(chip, part->address, (length + SPI_FLASH_SEC_SIZE) & ~(SPI_FLASH_SEC_SIZE - 1)) );

    // note writing to unaligned address
    ESP_ERROR_CHECK( esp_flash_write(chip, source, part->address + 1, length) );
}