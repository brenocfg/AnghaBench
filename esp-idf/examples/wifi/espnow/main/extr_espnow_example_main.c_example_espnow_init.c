#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int encrypt; int unicast; int broadcast; int len; int /*<<< orphan*/  dest_mac; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  delay; int /*<<< orphan*/  count; int /*<<< orphan*/  magic; scalar_t__ state; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  ifidx; int /*<<< orphan*/  channel; } ;
typedef  TYPE_1__ example_espnow_send_param_t ;
typedef  int /*<<< orphan*/  example_espnow_event_t ;
typedef  TYPE_1__ esp_now_peer_info_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ESPNOW_CHANNEL ; 
 scalar_t__ CONFIG_ESPNOW_PMK ; 
 int /*<<< orphan*/  CONFIG_ESPNOW_SEND_COUNT ; 
 int /*<<< orphan*/  CONFIG_ESPNOW_SEND_DELAY ; 
 int CONFIG_ESPNOW_SEND_LEN ; 
 int /*<<< orphan*/  ESPNOW_QUEUE_SIZE ; 
 int /*<<< orphan*/  ESPNOW_WIFI_IF ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_NOW_ETH_ALEN ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_now_add_peer (TYPE_1__*) ; 
 int /*<<< orphan*/  esp_now_deinit () ; 
 int /*<<< orphan*/  esp_now_init () ; 
 int /*<<< orphan*/  esp_now_register_recv_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_now_register_send_cb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_now_set_pmk (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_random () ; 
 int /*<<< orphan*/  example_espnow_data_prepare (TYPE_1__*) ; 
 int /*<<< orphan*/  example_espnow_recv_cb ; 
 int /*<<< orphan*/  example_espnow_send_cb ; 
 int /*<<< orphan*/  example_espnow_task ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_example_broadcast_mac ; 
 int /*<<< orphan*/ * s_example_espnow_queue ; 
 int /*<<< orphan*/  vSemaphoreDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xQueueCreate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int,TYPE_1__*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static esp_err_t example_espnow_init(void)
{
    example_espnow_send_param_t *send_param;

    s_example_espnow_queue = xQueueCreate(ESPNOW_QUEUE_SIZE, sizeof(example_espnow_event_t));
    if (s_example_espnow_queue == NULL) {
        ESP_LOGE(TAG, "Create mutex fail");
        return ESP_FAIL;
    }

    /* Initialize ESPNOW and register sending and receiving callback function. */
    ESP_ERROR_CHECK( esp_now_init() );
    ESP_ERROR_CHECK( esp_now_register_send_cb(example_espnow_send_cb) );
    ESP_ERROR_CHECK( esp_now_register_recv_cb(example_espnow_recv_cb) );

    /* Set primary master key. */
    ESP_ERROR_CHECK( esp_now_set_pmk((uint8_t *)CONFIG_ESPNOW_PMK) );

    /* Add broadcast peer information to peer list. */
    esp_now_peer_info_t *peer = malloc(sizeof(esp_now_peer_info_t));
    if (peer == NULL) {
        ESP_LOGE(TAG, "Malloc peer information fail");
        vSemaphoreDelete(s_example_espnow_queue);
        esp_now_deinit();
        return ESP_FAIL;
    }
    memset(peer, 0, sizeof(esp_now_peer_info_t));
    peer->channel = CONFIG_ESPNOW_CHANNEL;
    peer->ifidx = ESPNOW_WIFI_IF;
    peer->encrypt = false;
    memcpy(peer->peer_addr, s_example_broadcast_mac, ESP_NOW_ETH_ALEN);
    ESP_ERROR_CHECK( esp_now_add_peer(peer) );
    free(peer);

    /* Initialize sending parameters. */
    send_param = malloc(sizeof(example_espnow_send_param_t));
    memset(send_param, 0, sizeof(example_espnow_send_param_t));
    if (send_param == NULL) {
        ESP_LOGE(TAG, "Malloc send parameter fail");
        vSemaphoreDelete(s_example_espnow_queue);
        esp_now_deinit();
        return ESP_FAIL;
    }
    send_param->unicast = false;
    send_param->broadcast = true;
    send_param->state = 0;
    send_param->magic = esp_random();
    send_param->count = CONFIG_ESPNOW_SEND_COUNT;
    send_param->delay = CONFIG_ESPNOW_SEND_DELAY;
    send_param->len = CONFIG_ESPNOW_SEND_LEN;
    send_param->buffer = malloc(CONFIG_ESPNOW_SEND_LEN);
    if (send_param->buffer == NULL) {
        ESP_LOGE(TAG, "Malloc send buffer fail");
        free(send_param);
        vSemaphoreDelete(s_example_espnow_queue);
        esp_now_deinit();
        return ESP_FAIL;
    }
    memcpy(send_param->dest_mac, s_example_broadcast_mac, ESP_NOW_ETH_ALEN);
    example_espnow_data_prepare(send_param);

    xTaskCreate(example_espnow_task, "example_espnow_task", 2048, send_param, 4, NULL);

    return ESP_OK;
}