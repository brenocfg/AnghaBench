#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ (* esp_flash_wrsr_func_t ) (TYPE_2__*,scalar_t__) ;
struct TYPE_16__ {TYPE_1__* chip_drv; } ;
typedef  TYPE_2__ esp_flash_t ;
typedef  scalar_t__ (* esp_flash_rdsr_func_t ) (TYPE_2__*,scalar_t__*) ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* set_chip_write_protect ) (TYPE_2__*,int) ;scalar_t__ (* wait_idle ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_IDLE_TIMEOUT ; 
 int /*<<< orphan*/  ESP_EARLY_LOGD (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ESP_EARLY_LOGV (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ESP_ERR_FLASH_NO_RESPONSE ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int esp_flash_is_quad_mode (TYPE_2__*) ; 
 scalar_t__ stub1 (TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int) ; 
 scalar_t__ stub3 (TYPE_2__*,scalar_t__) ; 
 scalar_t__ stub4 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (TYPE_2__*,scalar_t__*) ; 
 int /*<<< orphan*/  stub6 (TYPE_2__*,int) ; 

esp_err_t spi_flash_common_set_io_mode(esp_flash_t *chip, esp_flash_wrsr_func_t wrsr_func, esp_flash_rdsr_func_t rdsr_func, uint32_t qe_sr_bit)
{
    esp_err_t ret = ESP_OK;
    const bool is_quad_mode = esp_flash_is_quad_mode(chip);
    bool update_config = false;
    const bool force_check = true; //in case some chips doesn't support erase QE

    bool need_check = is_quad_mode;
    if (force_check) {
        need_check = true;
    }

    uint32_t sr_update;
    if (need_check) {
        // Ensure quad modes are enabled, using the Quad Enable parameters supplied.
        uint32_t sr;
        ret = (*rdsr_func)(chip, &sr);
        if (ret != ESP_OK) {
            return ret;
        }
        ESP_EARLY_LOGD(TAG, "set_io_mode: status before 0x%x", sr);
        if (is_quad_mode) {
            sr_update = sr | qe_sr_bit;
        } else {
            sr_update = sr & (~qe_sr_bit);
        }
        ESP_EARLY_LOGV(TAG, "set_io_mode: status update 0x%x", sr_update);
        if (sr != sr_update) {
            update_config = true;
        }
    }

    if (update_config) {
        //some chips needs the write protect to be disabled before writing to Status Register
        chip->chip_drv->set_chip_write_protect(chip, false);

        ret = (*wrsr_func)(chip, sr_update);
        if (ret != ESP_OK) {
            return ret;
        }

        ret = chip->chip_drv->wait_idle(chip, DEFAULT_IDLE_TIMEOUT);
        if (ret != ESP_OK) {
            return ret;
        }

        /* Check the new QE bit has stayed set */
        uint32_t sr;
        ret = (*rdsr_func)(chip, &sr);
        if (ret != ESP_OK) {
            return ret;
        }
        ESP_EARLY_LOGD(TAG, "set_io_mode: status after 0x%x", sr);
        if (sr != sr_update) {
            ret = ESP_ERR_FLASH_NO_RESPONSE;
        }

        chip->chip_drv->set_chip_write_protect(chip, true);
    }
    return ret;
}