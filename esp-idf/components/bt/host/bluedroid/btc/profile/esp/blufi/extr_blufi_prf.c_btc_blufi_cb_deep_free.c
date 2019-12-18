#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  data; } ;
struct TYPE_15__ {int /*<<< orphan*/  pkey; } ;
struct TYPE_27__ {int /*<<< orphan*/  pkey; } ;
struct TYPE_26__ {int /*<<< orphan*/  cert; } ;
struct TYPE_25__ {int /*<<< orphan*/  cert; } ;
struct TYPE_24__ {int /*<<< orphan*/  cert; } ;
struct TYPE_23__ {int /*<<< orphan*/  name; } ;
struct TYPE_22__ {int /*<<< orphan*/  passwd; } ;
struct TYPE_21__ {int /*<<< orphan*/  ssid; } ;
struct TYPE_20__ {int /*<<< orphan*/  passwd; } ;
struct TYPE_19__ {int /*<<< orphan*/  ssid; } ;
struct TYPE_17__ {TYPE_11__ custom_data; TYPE_10__ server_pkey; TYPE_9__ client_pkey; TYPE_8__ server_cert; TYPE_7__ client_cert; TYPE_6__ ca; TYPE_5__ username; TYPE_4__ softap_passwd; TYPE_3__ softap_ssid; TYPE_2__ sta_passwd; TYPE_1__ sta_ssid; } ;
typedef  TYPE_12__ esp_blufi_cb_param_t ;
struct TYPE_18__ {int act; scalar_t__ arg; } ;
typedef  TYPE_13__ btc_msg_t ;

/* Variables and functions */
#define  ESP_BLUFI_EVENT_RECV_CA_CERT 138 
#define  ESP_BLUFI_EVENT_RECV_CLIENT_CERT 137 
#define  ESP_BLUFI_EVENT_RECV_CLIENT_PRIV_KEY 136 
#define  ESP_BLUFI_EVENT_RECV_CUSTOM_DATA 135 
#define  ESP_BLUFI_EVENT_RECV_SERVER_CERT 134 
#define  ESP_BLUFI_EVENT_RECV_SERVER_PRIV_KEY 133 
#define  ESP_BLUFI_EVENT_RECV_SOFTAP_PASSWD 132 
#define  ESP_BLUFI_EVENT_RECV_SOFTAP_SSID 131 
#define  ESP_BLUFI_EVENT_RECV_STA_PASSWD 130 
#define  ESP_BLUFI_EVENT_RECV_STA_SSID 129 
#define  ESP_BLUFI_EVENT_RECV_USERNAME 128 
 int /*<<< orphan*/  osi_free (int /*<<< orphan*/ ) ; 

void btc_blufi_cb_deep_free(btc_msg_t *msg)
{
    esp_blufi_cb_param_t *param = (esp_blufi_cb_param_t *)msg->arg;

    switch (msg->act) {
    case ESP_BLUFI_EVENT_RECV_STA_SSID:
        osi_free(param->sta_ssid.ssid);
        break;
    case ESP_BLUFI_EVENT_RECV_STA_PASSWD:
        osi_free(param->sta_passwd.passwd);
        break;
    case ESP_BLUFI_EVENT_RECV_SOFTAP_SSID:
        osi_free(param->softap_ssid.ssid);
        break;
    case ESP_BLUFI_EVENT_RECV_SOFTAP_PASSWD:
        osi_free(param->softap_passwd.passwd);
        break;
    case ESP_BLUFI_EVENT_RECV_USERNAME:
        osi_free(param->username.name);
        break;
    case ESP_BLUFI_EVENT_RECV_CA_CERT:
        osi_free(param->ca.cert);
        break;
    case ESP_BLUFI_EVENT_RECV_CLIENT_CERT:
        osi_free(param->client_cert.cert);
        break;
    case ESP_BLUFI_EVENT_RECV_SERVER_CERT:
        osi_free(param->server_cert.cert);
        break;
    case ESP_BLUFI_EVENT_RECV_CLIENT_PRIV_KEY:
        osi_free(param->client_pkey.pkey);
        break;
    case ESP_BLUFI_EVENT_RECV_SERVER_PRIV_KEY:
        osi_free(param->server_pkey.pkey);
        break;
    case ESP_BLUFI_EVENT_RECV_CUSTOM_DATA:
        osi_free(param->custom_data.data);
        break;
    default:
        break;
    }
}