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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  image_len; } ;
typedef  TYPE_1__ esp_image_metadata_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 scalar_t__ esp_image_verify_bootloader_data (TYPE_1__*) ; 

esp_err_t esp_image_verify_bootloader(uint32_t *length)
{
    esp_image_metadata_t data;
    esp_err_t err = esp_image_verify_bootloader_data(&data);
    if (length != NULL) {
        *length = (err == ESP_OK) ? data.image_len : 0;
    }
    return err;
}