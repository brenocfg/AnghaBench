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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct flash_test_ctx {int offset; int fail; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int SPI_FLASH_SEC_SIZE ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ spi_flash_erase_sector (int const) ; 
 scalar_t__ spi_flash_read (int const,int /*<<< orphan*/ *,int) ; 
 scalar_t__ spi_flash_write (int const,int /*<<< orphan*/  const*,int) ; 
 int start ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xSemaphoreGive (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flash_test_task(void *arg)
{
    struct flash_test_ctx *ctx = (struct flash_test_ctx *) arg;
    vTaskDelay(100 / portTICK_PERIOD_MS);
    const uint32_t sector = start / SPI_FLASH_SEC_SIZE + ctx->offset;
    printf("t%d\n", sector);
    printf("es%d\n", sector);
    if (spi_flash_erase_sector(sector) != ESP_OK) {
        ctx->fail = true;
        printf("Erase failed\r\n");
        xSemaphoreGive(ctx->done);
        vTaskDelete(NULL);
    }
    printf("ed%d\n", sector);

    vTaskDelay(0 / portTICK_PERIOD_MS);

    uint32_t val = 0xabcd1234;
    for (uint32_t offset = 0; offset < SPI_FLASH_SEC_SIZE; offset += 4) {
        if (spi_flash_write(sector * SPI_FLASH_SEC_SIZE + offset, (const uint8_t *) &val, 4) != ESP_OK) {
            printf("Write failed at offset=%d\r\n", offset);
            ctx->fail = true;
            break;
        }
    }
    printf("wd%d\n", sector);

    vTaskDelay(0 / portTICK_PERIOD_MS);

    uint32_t val_read;
    for (uint32_t offset = 0; offset < SPI_FLASH_SEC_SIZE; offset += 4) {
        if (spi_flash_read(sector * SPI_FLASH_SEC_SIZE + offset, (uint8_t *) &val_read, 4) != ESP_OK) {
            printf("Read failed at offset=%d\r\n", offset);
            ctx->fail = true;
            break;
        }
        if (val_read != val) {
            printf("Read invalid value=%08x at offset=%d\r\n", val_read, offset);
            ctx->fail = true;
            break;
        }
    }
    printf("td%d\n", sector);
    xSemaphoreGive(ctx->done);
    vTaskDelete(NULL);
}