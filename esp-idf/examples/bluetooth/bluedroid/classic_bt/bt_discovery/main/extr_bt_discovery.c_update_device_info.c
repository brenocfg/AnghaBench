#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  void* int8_t ;
typedef  int int32_t ;
struct TYPE_8__ {int type; size_t len; scalar_t__ val; } ;
typedef  TYPE_2__ esp_bt_gap_dev_prop_t ;
struct TYPE_7__ {size_t* bda; int num_prop; TYPE_2__* prop; } ;
struct TYPE_9__ {TYPE_1__ disc_res; } ;
typedef  TYPE_3__ esp_bt_gap_cb_param_t ;
struct TYPE_10__ {int dev_found; char* bda; char* bdname; size_t bdname_len; char* eir; size_t eir_len; int /*<<< orphan*/  state; void* rssi; int /*<<< orphan*/  cod; } ;
typedef  TYPE_4__ app_gap_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  APP_GAP_STATE_DEVICE_DISCOVER_COMPLETE ; 
 size_t ESP_BD_ADDR_LEN ; 
 scalar_t__ ESP_BT_COD_MAJOR_DEV_PHONE ; 
#define  ESP_BT_GAP_DEV_PROP_BDNAME 131 
#define  ESP_BT_GAP_DEV_PROP_COD 130 
#define  ESP_BT_GAP_DEV_PROP_EIR 129 
#define  ESP_BT_GAP_DEV_PROP_RSSI 128 
 size_t ESP_BT_GAP_MAX_BDNAME_LEN ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  GAP_TAG ; 
 int /*<<< orphan*/  bda2str (size_t*,char*,int) ; 
 int /*<<< orphan*/  esp_bt_gap_cancel_discovery () ; 
 scalar_t__ esp_bt_gap_get_cod_major_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_bt_gap_is_valid_cod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_name_from_eir (char*,char*,scalar_t__*) ; 
 TYPE_4__ m_dev_info ; 
 scalar_t__ memcmp (size_t*,char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,size_t*,size_t) ; 

__attribute__((used)) static void update_device_info(esp_bt_gap_cb_param_t *param)
{
    char bda_str[18];
    uint32_t cod = 0;
    int32_t rssi = -129; /* invalid value */
    esp_bt_gap_dev_prop_t *p;

    ESP_LOGI(GAP_TAG, "Device found: %s", bda2str(param->disc_res.bda, bda_str, 18));
    for (int i = 0; i < param->disc_res.num_prop; i++) {
        p = param->disc_res.prop + i;
        switch (p->type) {
        case ESP_BT_GAP_DEV_PROP_COD:
            cod = *(uint32_t *)(p->val);
            ESP_LOGI(GAP_TAG, "--Class of Device: 0x%x", cod);
            break;
        case ESP_BT_GAP_DEV_PROP_RSSI:
            rssi = *(int8_t *)(p->val);
            ESP_LOGI(GAP_TAG, "--RSSI: %d", rssi);
            break;
        case ESP_BT_GAP_DEV_PROP_BDNAME:
        default:
            break;
        }
    }

    /* search for device with MAJOR service class as "rendering" in COD */
    app_gap_cb_t *p_dev = &m_dev_info;
    if (p_dev->dev_found && 0 != memcmp(param->disc_res.bda, p_dev->bda, ESP_BD_ADDR_LEN)) {
        return;
    }

    if (!esp_bt_gap_is_valid_cod(cod) ||
            !(esp_bt_gap_get_cod_major_dev(cod) == ESP_BT_COD_MAJOR_DEV_PHONE)) {
        return;
    }

    memcpy(p_dev->bda, param->disc_res.bda, ESP_BD_ADDR_LEN);
    p_dev->dev_found = true;
    for (int i = 0; i < param->disc_res.num_prop; i++) {
        p = param->disc_res.prop + i;
        switch (p->type) {
        case ESP_BT_GAP_DEV_PROP_COD:
            p_dev->cod = *(uint32_t *)(p->val);
            break;
        case ESP_BT_GAP_DEV_PROP_RSSI:
            p_dev->rssi = *(int8_t *)(p->val);
            break;
        case ESP_BT_GAP_DEV_PROP_BDNAME: {
            uint8_t len = (p->len > ESP_BT_GAP_MAX_BDNAME_LEN) ? ESP_BT_GAP_MAX_BDNAME_LEN :
                          (uint8_t)p->len;
            memcpy(p_dev->bdname, (uint8_t *)(p->val), len);
            p_dev->bdname[len] = '\0';
            p_dev->bdname_len = len;
            break;
        }
        case ESP_BT_GAP_DEV_PROP_EIR: {
            memcpy(p_dev->eir, (uint8_t *)(p->val), p->len);
            p_dev->eir_len = p->len;
            break;
        }
        default:
            break;
        }
    }

    if (p_dev->eir && p_dev->bdname_len == 0) {
        get_name_from_eir(p_dev->eir, p_dev->bdname, &p_dev->bdname_len);
        ESP_LOGI(GAP_TAG, "Found a target device, address %s, name %s", bda_str, p_dev->bdname);
        p_dev->state = APP_GAP_STATE_DEVICE_DISCOVER_COMPLETE;
        ESP_LOGI(GAP_TAG, "Cancel device discovery ...");
        esp_bt_gap_cancel_discovery();
    }
}