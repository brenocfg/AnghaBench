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
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (scalar_t__) ; 
 scalar_t__ ESP_ERR_INVALID_SIZE ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ sdmmc_io_get_cis_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const,size_t*) ; 
 int /*<<< orphan*/  sdmmc_io_print_cis_info (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t print_sdio_cis_information(sdmmc_card_t* card)
{
    const size_t cis_buffer_size = 256;
    uint8_t cis_buffer[cis_buffer_size];
    size_t cis_data_len = 1024; //specify maximum searching range to avoid infinite loop
    esp_err_t ret = ESP_OK;

    ret = sdmmc_io_get_cis_data(card, cis_buffer, cis_buffer_size, &cis_data_len);
    if (ret == ESP_ERR_INVALID_SIZE) {
        int temp_buf_size = cis_data_len;
        uint8_t* temp_buf = malloc(temp_buf_size);
        assert(temp_buf);

        ESP_LOGW(TAG, "CIS data longer than expected, temporary buffer allocated.");
        ret = sdmmc_io_get_cis_data(card, temp_buf, temp_buf_size, &cis_data_len);
        ESP_ERROR_CHECK(ret);

        sdmmc_io_print_cis_info(temp_buf, cis_data_len, NULL);

        free(temp_buf);
    } else if (ret == ESP_OK) {
        sdmmc_io_print_cis_info(cis_buffer, cis_data_len, NULL);
    } else {
        //including ESP_ERR_NOT_FOUND
        ESP_LOGE(TAG, "failed to get the entire CIS data.");
        abort();
    }
    return ESP_OK;
}