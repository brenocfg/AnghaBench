#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ uint32_t ;
typedef  TYPE_4__ esp_local_ctrl_prop_val_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_21__ {int /*<<< orphan*/  status; } ;
struct TYPE_20__ {TYPE_7__* resp_set_prop_vals; int /*<<< orphan*/  payload_case; TYPE_3__* cmd_set_prop_vals; } ;
struct TYPE_18__ {size_t n_props; TYPE_2__** props; } ;
struct TYPE_16__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct TYPE_17__ {TYPE_1__ value; TYPE_4__ index; } ;
typedef  TYPE_6__ LocalCtrlMessage ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  LOCAL_CTRL_MESSAGE__PAYLOAD_RESP_SET_PROP_VALS ; 
 int /*<<< orphan*/  RespSetPropertyValues ; 
 int /*<<< orphan*/  SAFE_ALLOCATION (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_4__* calloc (size_t,int) ; 
 int /*<<< orphan*/  err_to_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_local_ctrl_set_prop_values (size_t,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_7__* resp_payload ; 
 int /*<<< orphan*/  resp_set_property_values__init (TYPE_7__*) ; 

__attribute__((used)) static esp_err_t cmd_set_prop_vals_handler(LocalCtrlMessage *req,
                                           LocalCtrlMessage *resp, void **ctx)
{
    SAFE_ALLOCATION(RespSetPropertyValues, resp_payload);
    resp_set_property_values__init(resp_payload);

    uint32_t *idxs = calloc(req->cmd_set_prop_vals->n_props, sizeof(uint32_t));
    esp_local_ctrl_prop_val_t *vals = calloc(req->cmd_set_prop_vals->n_props,
                                             sizeof(esp_local_ctrl_prop_val_t));
    if (!idxs || !vals) {
        ESP_LOGE(TAG, "Failed to allocate memory for setting values");
        free(idxs);
        free(vals);
        return ESP_ERR_NO_MEM;
    }
    for (size_t i = 0; i < req->cmd_set_prop_vals->n_props; i++) {
        idxs[i]      = req->cmd_set_prop_vals->props[i]->index;
        vals[i].data = req->cmd_set_prop_vals->props[i]->value.data;
        vals[i].size = req->cmd_set_prop_vals->props[i]->value.len;
    }

    esp_err_t ret = esp_local_ctrl_set_prop_values(req->cmd_set_prop_vals->n_props,
                                                   idxs, vals);
    resp_payload->status = err_to_status(ret);
    resp->payload_case = LOCAL_CTRL_MESSAGE__PAYLOAD_RESP_SET_PROP_VALS;
    resp->resp_set_prop_vals = resp_payload;
    free(idxs);
    free(vals);

    /* Unless it's a fatal error, always return ESP_OK, otherwise
     * the underlying connection will be closed by protocomm */
    return ESP_OK;
}