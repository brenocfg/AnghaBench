#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_8__ {size_t count; int /*<<< orphan*/  status; } ;
struct TYPE_7__ {TYPE_2__* resp_get_prop_count; int /*<<< orphan*/  payload_case; } ;
typedef  TYPE_1__ LocalCtrlMessage ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGD (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  LOCAL_CTRL_MESSAGE__PAYLOAD_RESP_GET_PROP_COUNT ; 
 int /*<<< orphan*/  RespGetPropertyCount ; 
 int /*<<< orphan*/  SAFE_ALLOCATION (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  err_to_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_local_ctrl_get_prop_count (size_t*) ; 
 int /*<<< orphan*/  resp_get_property_count__init (TYPE_2__*) ; 
 TYPE_2__* resp_payload ; 

__attribute__((used)) static esp_err_t cmd_get_prop_count_handler(LocalCtrlMessage *req,
                                            LocalCtrlMessage *resp, void **ctx)
{
    SAFE_ALLOCATION(RespGetPropertyCount, resp_payload);
    resp_get_property_count__init(resp_payload);

    size_t prop_count = 0;
    resp_payload->status = err_to_status(esp_local_ctrl_get_prop_count(&prop_count));
    resp_payload->count = prop_count;
    resp->payload_case = LOCAL_CTRL_MESSAGE__PAYLOAD_RESP_GET_PROP_COUNT;
    resp->resp_get_prop_count = resp_payload;
    ESP_LOGD(TAG, "Got properties count %d", prop_count);
    return ESP_OK;
}