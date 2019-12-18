#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* p_req_cb ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {TYPE_1__ app_cb; scalar_t__ in_use; } ;
typedef  TYPE_2__ tGATT_REG ;
typedef  int /*<<< orphan*/  tGATT_IF ;
typedef  int /*<<< orphan*/  tGATTS_REQ_TYPE ;
typedef  int /*<<< orphan*/  tGATTS_DATA ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_GET_GATT_IF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  GATT_TRACE_WARNING (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* gatt_get_regcb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gatt_sr_send_req_callback(UINT16 conn_id,
                               UINT32 trans_id,
                               tGATTS_REQ_TYPE type, tGATTS_DATA *p_data)
{
    tGATT_IF        gatt_if = GATT_GET_GATT_IF(conn_id);
    tGATT_REG       *p_reg = gatt_get_regcb(gatt_if);

    if (!p_reg ) {
        GATT_TRACE_ERROR ("p_reg not found discard request");
        return;
    }

    if ( p_reg->in_use &&
            p_reg->app_cb.p_req_cb) {
        (*p_reg->app_cb.p_req_cb)(conn_id, trans_id, type, p_data);
    } else {
        GATT_TRACE_WARNING("Call back not found for application conn_id=%d", conn_id);
    }

}