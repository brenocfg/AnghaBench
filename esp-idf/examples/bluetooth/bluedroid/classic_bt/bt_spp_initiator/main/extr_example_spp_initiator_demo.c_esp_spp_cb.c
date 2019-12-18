#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  cong; int /*<<< orphan*/  len; } ;
struct TYPE_12__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  cong; } ;
struct TYPE_11__ {int /*<<< orphan*/  handle; } ;
struct TYPE_10__ {int /*<<< orphan*/ * scn; int /*<<< orphan*/  status; int /*<<< orphan*/  scn_num; } ;
struct TYPE_14__ {TYPE_4__ write; TYPE_3__ cong; TYPE_2__ srv_open; TYPE_1__ disc_comp; } ;
typedef  TYPE_5__ esp_spp_cb_param_t ;
typedef  int esp_spp_cb_event_t ;
struct TYPE_15__ {int tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_BT_CONNECTABLE ; 
 int /*<<< orphan*/  ESP_BT_GENERAL_DISCOVERABLE ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,...) ; 
#define  ESP_SPP_CLOSE_EVT 137 
#define  ESP_SPP_CL_INIT_EVT 136 
#define  ESP_SPP_CONG_EVT 135 
#define  ESP_SPP_DATA_IND_EVT 134 
#define  ESP_SPP_DISCOVERY_COMP_EVT 133 
#define  ESP_SPP_INIT_EVT 132 
#define  ESP_SPP_OPEN_EVT 131 
#define  ESP_SPP_SRV_OPEN_EVT 130 
#define  ESP_SPP_START_EVT 129 
 int /*<<< orphan*/  ESP_SPP_SUCCESS ; 
#define  ESP_SPP_WRITE_EVT 128 
 int /*<<< orphan*/  EXAMPLE_DEVICE_NAME ; 
 int /*<<< orphan*/  SPP_DATA_LEN ; 
 int /*<<< orphan*/  SPP_TAG ; 
 int /*<<< orphan*/  data_num ; 
 int /*<<< orphan*/  esp_bt_dev_set_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_bt_gap_set_scan_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_bt_gap_start_discovery (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_log_buffer_hex (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_spp_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_spp_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inq_len ; 
 int /*<<< orphan*/  inq_mode ; 
 int /*<<< orphan*/  inq_num_rsps ; 
 int /*<<< orphan*/  peer_bd_addr ; 
 int /*<<< orphan*/  print_speed () ; 
 int /*<<< orphan*/  role_master ; 
 int /*<<< orphan*/  sec_mask ; 
 int /*<<< orphan*/  spp_data ; 
 TYPE_6__ time_new ; 
 TYPE_6__ time_old ; 

__attribute__((used)) static void esp_spp_cb(esp_spp_cb_event_t event, esp_spp_cb_param_t *param)
{
    switch (event) {
    case ESP_SPP_INIT_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_INIT_EVT");
        esp_bt_dev_set_device_name(EXAMPLE_DEVICE_NAME);
        esp_bt_gap_set_scan_mode(ESP_BT_CONNECTABLE, ESP_BT_GENERAL_DISCOVERABLE);
        esp_bt_gap_start_discovery(inq_mode, inq_len, inq_num_rsps);

        break;
    case ESP_SPP_DISCOVERY_COMP_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_DISCOVERY_COMP_EVT status=%d scn_num=%d",param->disc_comp.status, param->disc_comp.scn_num);
        if (param->disc_comp.status == ESP_SPP_SUCCESS) {
            esp_spp_connect(sec_mask, role_master, param->disc_comp.scn[0], peer_bd_addr);
        }
        break;
    case ESP_SPP_OPEN_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_OPEN_EVT");
        esp_spp_write(param->srv_open.handle, SPP_DATA_LEN, spp_data);
        gettimeofday(&time_old, NULL);
        break;
    case ESP_SPP_CLOSE_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_CLOSE_EVT");
        break;
    case ESP_SPP_START_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_START_EVT");
        break;
    case ESP_SPP_CL_INIT_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_CL_INIT_EVT");
        break;
    case ESP_SPP_DATA_IND_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_DATA_IND_EVT");
        break;
    case ESP_SPP_CONG_EVT:
#if (SPP_SHOW_MODE == SPP_SHOW_DATA)
        ESP_LOGI(SPP_TAG, "ESP_SPP_CONG_EVT cong=%d", param->cong.cong);
#endif
        if (param->cong.cong == 0) {
            esp_spp_write(param->cong.handle, SPP_DATA_LEN, spp_data);
        }
        break;
    case ESP_SPP_WRITE_EVT:
#if (SPP_SHOW_MODE == SPP_SHOW_DATA)
        ESP_LOGI(SPP_TAG, "ESP_SPP_WRITE_EVT len=%d cong=%d", param->write.len , param->write.cong);
        esp_log_buffer_hex("",spp_data,SPP_DATA_LEN);
#else
        gettimeofday(&time_new, NULL);
        data_num += param->write.len;
        if (time_new.tv_sec - time_old.tv_sec >= 3) {
            print_speed();
        }
#endif
        if (param->write.cong == 0) {
            esp_spp_write(param->write.handle, SPP_DATA_LEN, spp_data);
        }
        break;
    case ESP_SPP_SRV_OPEN_EVT:
        ESP_LOGI(SPP_TAG, "ESP_SPP_SRV_OPEN_EVT");
        break;
    default:
        break;
    }
}