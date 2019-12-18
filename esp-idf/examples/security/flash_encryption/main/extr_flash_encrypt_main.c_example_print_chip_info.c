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
struct TYPE_3__ {int cores; int features; int revision; } ;
typedef  TYPE_1__ esp_chip_info_t ;

/* Variables and functions */
 int CHIP_FEATURE_BLE ; 
 int CHIP_FEATURE_BT ; 
 int CHIP_FEATURE_EMB_FLASH ; 
 int /*<<< orphan*/  esp_chip_info (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int spi_flash_get_chip_size () ; 

__attribute__((used)) static void example_print_chip_info(void)
{
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
}