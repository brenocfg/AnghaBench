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
struct TYPE_8__ {int /*<<< orphan*/  gpio_int; int /*<<< orphan*/  gpio_cs; int /*<<< orphan*/  gpio_sck; int /*<<< orphan*/  gpio_mosi; int /*<<< orphan*/  gpio_miso; } ;
typedef  TYPE_1__ sdspi_slot_config_t ;
typedef  int /*<<< orphan*/  sdmmc_slot_config_t ;
struct TYPE_9__ {int /*<<< orphan*/  max_freq_khz; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ sdmmc_host_t ;
typedef  int /*<<< orphan*/  sdmmc_card_t ;
typedef  int /*<<< orphan*/  esp_slave_context_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  ESP_SLAVE_DEFAULT_CONTEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HSPI_HOST ; 
 int /*<<< orphan*/  SDIO_SLAVE_SLOT1_IOMUX_PIN_NUM_CLK ; 
 int /*<<< orphan*/  SDIO_SLAVE_SLOT1_IOMUX_PIN_NUM_CMD ; 
 int /*<<< orphan*/  SDIO_SLAVE_SLOT1_IOMUX_PIN_NUM_D0 ; 
 int /*<<< orphan*/  SDIO_SLAVE_SLOT1_IOMUX_PIN_NUM_D1 ; 
 int /*<<< orphan*/  SDIO_SLAVE_SLOT1_IOMUX_PIN_NUM_D3 ; 
 int /*<<< orphan*/  SDMMC_FREQ_DEFAULT ; 
 int /*<<< orphan*/  SDMMC_FREQ_HIGHSPEED ; 
 TYPE_2__ SDMMC_HOST_DEFAULT () ; 
 int /*<<< orphan*/  SDMMC_HOST_FLAG_1BIT ; 
 int /*<<< orphan*/  SDMMC_HOST_FLAG_4BIT ; 
 int /*<<< orphan*/  SDMMC_HOST_SLOT_1 ; 
 int /*<<< orphan*/  SDMMC_SLOT_CONFIG_DEFAULT () ; 
 TYPE_2__ SDSPI_HOST_DEFAULT () ; 
 TYPE_1__ SDSPI_SLOT_CONFIG_DEFAULT () ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_slave_init_io (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_d2_set_high () ; 
 int /*<<< orphan*/  gpio_install_isr_service (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_pulldown_dis (int) ; 
 int /*<<< orphan*/  gpio_pullup_en (int) ; 
 scalar_t__ malloc (int) ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  print_sdio_cis_information (int /*<<< orphan*/ *) ; 
 scalar_t__ sdmmc_card_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdmmc_card_print_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdmmc_host_init () ; 
 int /*<<< orphan*/  sdmmc_host_init_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdspi_host_init () ; 
 int /*<<< orphan*/  sdspi_host_init_slot (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

esp_err_t slave_init(esp_slave_context_t *context)
{
    esp_err_t err;
    /* Probe */
#ifndef CONFIG_EXAMPLE_SDIO_OVER_SPI
    sdmmc_host_t config = SDMMC_HOST_DEFAULT();
#ifdef CONFIG_EXAMPLE_SDIO_4BIT
    ESP_LOGI(TAG, "Probe using SD 4-bit...\n");
    config.flags = SDMMC_HOST_FLAG_4BIT;
#else
    ESP_LOGI(TAG, "Probe using SD 1-bit...\n");
    config.flags = SDMMC_HOST_FLAG_1BIT;
#endif

#ifdef CONFIG_EXAMPLE_SDIO_HIGHSPEED
    config.max_freq_khz = SDMMC_FREQ_HIGHSPEED;
#else
    config.max_freq_khz = SDMMC_FREQ_DEFAULT;
#endif

    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    /* Note: For small devkits there may be no pullups on the board.
       This enables the internal pullups to help evaluate the driver quickly.
       However the internal pullups are not sufficient and not reliable,
       please make sure external pullups are connected to the bus in your
       real design.
    */
    //slot_config.flags = SDMMC_SLOT_FLAG_INTERNAL_PULLUP;
    err = sdmmc_host_init();
    ESP_ERROR_CHECK(err);

    err = sdmmc_host_init_slot(SDMMC_HOST_SLOT_1, &slot_config);
    ESP_ERROR_CHECK(err);
#else   //over SPI
    sdmmc_host_t config = SDSPI_HOST_DEFAULT();

    sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
    slot_config.gpio_miso = SDIO_SLAVE_SLOT1_IOMUX_PIN_NUM_D0;
    slot_config.gpio_mosi = SDIO_SLAVE_SLOT1_IOMUX_PIN_NUM_CMD;
    slot_config.gpio_sck  = SDIO_SLAVE_SLOT1_IOMUX_PIN_NUM_CLK;
    slot_config.gpio_cs   = SDIO_SLAVE_SLOT1_IOMUX_PIN_NUM_D3;
    slot_config.gpio_int = SDIO_SLAVE_SLOT1_IOMUX_PIN_NUM_D1;

    err = gpio_install_isr_service(0);
    ESP_ERROR_CHECK(err);
    err = sdspi_host_init();
    ESP_ERROR_CHECK(err);

    err = sdspi_host_init_slot(HSPI_HOST, &slot_config);
    ESP_ERROR_CHECK(err);
    ESP_LOGI(TAG, "Probe using SPI...\n");

    //we have to pull up all the slave pins even when the pin is not used
    gpio_d2_set_high();
#endif  //over SPI
    sdmmc_card_t *card = (sdmmc_card_t *)malloc(sizeof(sdmmc_card_t));
    if (card == NULL) {
        return ESP_ERR_NO_MEM;
    }
    for (;;) {
        if (sdmmc_card_init(&config, card) == ESP_OK) {
            break;
        }
        ESP_LOGW(TAG, "slave init failed, retry...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    sdmmc_card_print_info(stdout, card);

    gpio_pullup_en(14);
    gpio_pulldown_dis(14);
    gpio_pullup_en(15);
    gpio_pulldown_dis(15);
    gpio_pullup_en(2);
    gpio_pulldown_dis(2);
    gpio_pullup_en(4);
    gpio_pulldown_dis(4);
    gpio_pullup_en(12);
    gpio_pulldown_dis(12);
    gpio_pullup_en(13);
    gpio_pulldown_dis(13);

    *context = ESP_SLAVE_DEFAULT_CONTEXT(card);
    esp_err_t ret = esp_slave_init_io(context);
    ESP_ERROR_CHECK(ret);

    ret = print_sdio_cis_information(card);
    ESP_ERROR_CHECK(ret);
    return ret;
}