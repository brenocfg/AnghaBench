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
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_efuse_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFUSE_LOCK_ACQUIRE () ; 
 int /*<<< orphan*/  EFUSE_LOCK_RELEASE () ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  esp_efuse_utility_fill_buff ; 
 int /*<<< orphan*/  esp_efuse_utility_get_number_of_items (size_t,int) ; 
 int /*<<< orphan*/  esp_efuse_utility_process (int /*<<< orphan*/  const**,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t esp_efuse_read_field_blob(const esp_efuse_desc_t* field[], void* dst, size_t dst_size_bits)
{
    EFUSE_LOCK_ACQUIRE();
    esp_err_t err = ESP_OK;
    if (field == NULL || dst == NULL || dst_size_bits == 0) {
        err = ESP_ERR_INVALID_ARG;
    } else {
        memset((uint8_t *)dst, 0, esp_efuse_utility_get_number_of_items(dst_size_bits, 8));
        err = esp_efuse_utility_process(field, dst, dst_size_bits, esp_efuse_utility_fill_buff);
    }
    EFUSE_LOCK_RELEASE();
    return err;
}