#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {struct TYPE_15__* mac; } ;
typedef  TYPE_1__ const uint8_t ;
typedef  int /*<<< orphan*/  phy_rf_module_t ;
typedef  TYPE_1__ esp_phy_init_data_t ;
typedef  scalar_t__ esp_phy_calibration_mode_t ;
typedef  TYPE_1__ const esp_phy_calibration_data_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ DEEPSLEEP_RESET ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ ESP_RST_BROWNOUT ; 
 scalar_t__ PHY_RF_CAL_FULL ; 
 scalar_t__ PHY_RF_CAL_NONE ; 
 scalar_t__ PHY_RF_CAL_PARTIAL ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  esp_efuse_mac_get_default (TYPE_1__ const*) ; 
 TYPE_1__* esp_phy_get_init_data () ; 
 scalar_t__ esp_phy_load_cal_data_from_nvs (TYPE_1__ const*) ; 
 int /*<<< orphan*/  esp_phy_reduce_tx_power (TYPE_1__*) ; 
 int /*<<< orphan*/  esp_phy_release_init_data (TYPE_1__ const*) ; 
 int /*<<< orphan*/  esp_phy_rf_init (TYPE_1__ const*,scalar_t__,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_phy_store_cal_data_to_nvs (TYPE_1__ const*) ; 
 scalar_t__ esp_reset_reason () ; 
 int /*<<< orphan*/  free (TYPE_1__ const*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 
 scalar_t__ rtc_get_reset_reason (int /*<<< orphan*/ ) ; 

void esp_phy_load_cal_and_init(phy_rf_module_t module)
{
    esp_phy_calibration_data_t* cal_data =
            (esp_phy_calibration_data_t*) calloc(sizeof(esp_phy_calibration_data_t), 1);
    if (cal_data == NULL) {
        ESP_LOGE(TAG, "failed to allocate memory for RF calibration data");
        abort();
    }

#if CONFIG_ESP32_REDUCE_PHY_TX_POWER
    const esp_phy_init_data_t* phy_init_data = esp_phy_get_init_data();
    if (phy_init_data == NULL) {
        ESP_LOGE(TAG, "failed to obtain PHY init data");
        abort();
    }

    esp_phy_init_data_t* init_data = (esp_phy_init_data_t*) malloc(sizeof(esp_phy_init_data_t));
    if (init_data == NULL) {
        ESP_LOGE(TAG, "failed to allocate memory for phy init data");
        abort();
    }

    memcpy(init_data, phy_init_data, sizeof(esp_phy_init_data_t));
#if CONFIG_IDF_TARGET_ESP32
    // ToDo: remove once esp_reset_reason is supported on esp32s2
    if (esp_reset_reason() == ESP_RST_BROWNOUT) {
        esp_phy_reduce_tx_power(init_data);
    }
#endif
#else
    const esp_phy_init_data_t* init_data = esp_phy_get_init_data();
    if (init_data == NULL) {
        ESP_LOGE(TAG, "failed to obtain PHY init data");
        abort();
    }
#endif

#ifdef CONFIG_ESP32_PHY_CALIBRATION_AND_DATA_STORAGE
    esp_phy_calibration_mode_t calibration_mode = PHY_RF_CAL_PARTIAL;
    uint8_t sta_mac[6];
    if (rtc_get_reset_reason(0) == DEEPSLEEP_RESET) {
        calibration_mode = PHY_RF_CAL_NONE;
    }
    esp_err_t err = esp_phy_load_cal_data_from_nvs(cal_data);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "failed to load RF calibration data (0x%x), falling back to full calibration", err);
        calibration_mode = PHY_RF_CAL_FULL;
    }

    esp_efuse_mac_get_default(sta_mac);
    memcpy(cal_data->mac, sta_mac, 6);
    esp_phy_rf_init(init_data, calibration_mode, cal_data, module);

    if (calibration_mode != PHY_RF_CAL_NONE && err != ESP_OK) {
        err = esp_phy_store_cal_data_to_nvs(cal_data);
    } else {
        err = ESP_OK;
    }
#else
    esp_phy_rf_init(init_data, PHY_RF_CAL_FULL, cal_data, module);
#endif

#if CONFIG_ESP32_REDUCE_PHY_TX_POWER
    esp_phy_release_init_data(phy_init_data);
    free(init_data);
#else
    esp_phy_release_init_data(init_data);
#endif

    free(cal_data); // PHY maintains a copy of calibration data, so we can free this
}