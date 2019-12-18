#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  value; int /*<<< orphan*/  auth_req; int /*<<< orphan*/  len; int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; int /*<<< orphan*/  conn_id; } ;
typedef  TYPE_2__ tGATT_VALUE ;
typedef  scalar_t__ tBTA_GATT_STATUS ;
struct TYPE_11__ {int /*<<< orphan*/  write_type; int /*<<< orphan*/  len; int /*<<< orphan*/  p_value; int /*<<< orphan*/  auth_req; int /*<<< orphan*/  offset; int /*<<< orphan*/  handle; } ;
struct TYPE_13__ {TYPE_1__ api_write; } ;
typedef  TYPE_3__ tBTA_GATTC_DATA ;
struct TYPE_14__ {int /*<<< orphan*/  bta_conn_id; TYPE_3__* p_q_cmd; } ;
typedef  TYPE_4__ tBTA_GATTC_CLCB ;

/* Variables and functions */
 scalar_t__ BTA_GATT_OK ; 
 int /*<<< orphan*/  GATTC_OPTYPE_WRITE ; 
 scalar_t__ GATTC_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  bta_gattc_cmpl_sendmsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_gattc_enqueue (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  bta_gattc_pop_command_to_send (TYPE_4__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_gattc_write(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    if (!bta_gattc_enqueue(p_clcb, p_data)) {
        return;
    }

    tBTA_GATT_STATUS    status = BTA_GATT_OK;
    tGATT_VALUE attr;

    attr.conn_id = p_clcb->bta_conn_id;
    attr.handle = p_data->api_write.handle;
    attr.offset = p_data->api_write.offset;
    attr.len    = p_data->api_write.len;
    attr.auth_req = p_data->api_write.auth_req;

    if (p_data->api_write.p_value) {
        memcpy(attr.value, p_data->api_write.p_value, p_data->api_write.len);
    }

    status = GATTC_Write(p_clcb->bta_conn_id, p_data->api_write.write_type, &attr);

    /* write fail */
    if (status != BTA_GATT_OK) {
        /* Dequeue the data, if it was enqueued */
        if (p_clcb->p_q_cmd == p_data) {
            p_clcb->p_q_cmd = NULL;
            bta_gattc_pop_command_to_send(p_clcb);
        }

        bta_gattc_cmpl_sendmsg(p_clcb->bta_conn_id, GATTC_OPTYPE_WRITE, status, NULL);
    }
}