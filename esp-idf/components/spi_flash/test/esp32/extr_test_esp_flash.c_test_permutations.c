#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  large_const_buffer ;
struct TYPE_10__ {int host_id; void* speed; void* io_mode; } ;
typedef  TYPE_1__ flashtest_config_t ;
struct TYPE_11__ {scalar_t__ size; } ;
typedef  TYPE_2__ esp_partition_t ;
typedef  int /*<<< orphan*/  esp_flash_t ;
typedef  scalar_t__ esp_flash_speed_t ;
typedef  scalar_t__ esp_flash_io_mode_t ;

/* Variables and functions */
 scalar_t__ ESP_FLASH_SPEED_MAX ; 
 void* ESP_FLASH_SPEED_MIN ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ SPI_FLASH_READ_MODE_MAX ; 
 void* SPI_FLASH_READ_MODE_MIN ; 
 scalar_t__ SPI_FLASH_SEC_SIZE ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_2__* get_test_data_partition () ; 
 int /*<<< orphan*/ * malloc (int const) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  read_and_check (int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  setup_new_chip (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  srand (int) ; 
 int /*<<< orphan*/  teardown_test_chip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  write_large_buffer (int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/ *,int const) ; 

void test_permutations(flashtest_config_t* config)
{
    //replace config pointer with pointer to internal temporary config
    flashtest_config_t temp_cfg;
    memcpy(&temp_cfg, config, sizeof(flashtest_config_t));
    flashtest_config_t* cfg = &temp_cfg;
    esp_flash_t* chip;

    const int length = sizeof(large_const_buffer);
    uint8_t *source_buf = malloc(length);
    TEST_ASSERT_NOT_NULL(source_buf);
    srand(778);
    for (int i = 0; i < length; i++) {
        source_buf[i] = rand();
    }

    const esp_partition_t *part = get_test_data_partition();
    TEST_ASSERT(part->size > length + 2 + SPI_FLASH_SEC_SIZE);

    //write data to be read, and use the lowest speed to write and read to make sure success
    cfg->io_mode = SPI_FLASH_READ_MODE_MIN;
    cfg->speed = ESP_FLASH_SPEED_MIN;
    setup_new_chip(cfg, &chip);
    write_large_buffer(chip, part, source_buf, length);
    read_and_check(chip, part, source_buf, length);
    teardown_test_chip(chip, cfg->host_id);


    if (config->host_id != -1) {
        esp_flash_speed_t speed = ESP_FLASH_SPEED_MIN;
        while (speed != ESP_FLASH_SPEED_MAX) {
            //test io_mode in the inner loop to test QE set/clear function, since
            //the io mode will switch frequently.
            esp_flash_io_mode_t io_mode = SPI_FLASH_READ_MODE_MIN;
            while (io_mode != SPI_FLASH_READ_MODE_MAX) {
                ESP_LOGI(TAG, "test flash io mode: %d, speed: %d", io_mode, speed);
                cfg->io_mode = io_mode;
                cfg->speed = speed;
                setup_new_chip(cfg, &chip);
                read_and_check(chip, part, source_buf, length);
                teardown_test_chip(chip, cfg->host_id);
                io_mode++;
            }
            speed++;
        }
    } else {
        //test main flash
        write_large_buffer(NULL, part, source_buf, length);
        read_and_check(NULL, part, source_buf, length);
    }

    free(source_buf);
}