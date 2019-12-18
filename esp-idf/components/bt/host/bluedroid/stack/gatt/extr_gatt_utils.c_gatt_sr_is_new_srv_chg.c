#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* p_new_srv_start; } ;
typedef  TYPE_1__ tGATTS_PENDING_NEW_SRV_START ;
struct TYPE_6__ {scalar_t__ svc_inst; int /*<<< orphan*/  svc_uuid; int /*<<< orphan*/  app_uuid128; } ;
typedef  TYPE_2__ tGATTS_HNDL_RANGE ;
typedef  int /*<<< orphan*/  tBT_UUID ;
typedef  int /*<<< orphan*/  list_t ;
typedef  int /*<<< orphan*/  list_node_t ;
typedef  scalar_t__ UINT16 ;
struct TYPE_7__ {int /*<<< orphan*/  pending_new_srv_start_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/ * fixed_queue_get_list (int /*<<< orphan*/ ) ; 
 scalar_t__ fixed_queue_is_empty (int /*<<< orphan*/ ) ; 
 TYPE_4__ gatt_cb ; 
 scalar_t__ gatt_uuid_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * list_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* list_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * list_next (int /*<<< orphan*/  const*) ; 
 scalar_t__ list_node (int /*<<< orphan*/  const*) ; 

tGATTS_PENDING_NEW_SRV_START *gatt_sr_is_new_srv_chg(tBT_UUID *p_app_uuid128, tBT_UUID *p_svc_uuid, UINT16 svc_inst)
{
    tGATTS_PENDING_NEW_SRV_START *p_buf = NULL;

    if (fixed_queue_is_empty(gatt_cb.pending_new_srv_start_q)) {
        return NULL;
	}

    list_t *list = fixed_queue_get_list(gatt_cb.pending_new_srv_start_q);
    for (const list_node_t *node = list_begin(list); node != list_end(list);
         node = list_next(node)) {
        p_buf = (tGATTS_PENDING_NEW_SRV_START *)list_node(node);
        tGATTS_HNDL_RANGE *p = p_buf->p_new_srv_start;
        if (gatt_uuid_compare(*p_app_uuid128, p->app_uuid128)
            && gatt_uuid_compare (*p_svc_uuid, p->svc_uuid)
            && (svc_inst == p->svc_inst)) {
            GATT_TRACE_DEBUG("gatt_sr_is_new_srv_chg: Yes");
            break;
        }
    }

    return p_buf;
}