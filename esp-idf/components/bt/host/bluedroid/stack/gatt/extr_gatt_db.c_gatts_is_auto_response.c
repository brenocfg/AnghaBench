#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * p_attr_list; } ;
typedef  TYPE_2__ tGATT_SVC_DB ;
struct TYPE_8__ {TYPE_2__ svc_db; } ;
typedef  TYPE_3__ tGATT_HDL_LIST_ELEM ;
struct TYPE_6__ {scalar_t__ auto_rsp; } ;
struct TYPE_9__ {scalar_t__ handle; TYPE_1__ control; int /*<<< orphan*/ * p_value; scalar_t__ p_next; } ;
typedef  TYPE_4__ tGATT_ATTR16 ;
typedef  scalar_t__ UINT16 ;
typedef  int BOOLEAN ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ GATT_RSP_BY_STACK ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 TYPE_3__* gatt_find_hdl_buffer_by_attr_handle (scalar_t__) ; 

BOOLEAN gatts_is_auto_response(UINT16 attr_handle)
{
    tGATT_HDL_LIST_ELEM  *p_decl = NULL;
    BOOLEAN rsp = FALSE;
    tGATT_SVC_DB *p_db = NULL;
    if ((p_decl = gatt_find_hdl_buffer_by_attr_handle(attr_handle)) == NULL) {
        GATT_TRACE_DEBUG("Service not created\n");
        return rsp;
    }

    p_db = &p_decl->svc_db;

    tGATT_ATTR16  *p_cur, *p_next;

    if (p_db == NULL) {
        GATT_TRACE_DEBUG("gatts_get_attribute_value Fail:p_db is NULL.\n");
        return rsp;
    }
    if (p_db->p_attr_list == NULL) {
        GATT_TRACE_DEBUG("gatts_get_attribute_value Fail:p_db->p_attr_list is NULL.\n");
        return rsp;
    }

    p_cur    =  (tGATT_ATTR16 *) p_db->p_attr_list;
    p_next  = (tGATT_ATTR16 *) p_cur->p_next;

    for (; p_cur != NULL && p_next != NULL;
            p_cur = p_next, p_next = (tGATT_ATTR16 *)p_next->p_next) {
        if (p_cur->handle == attr_handle) {
            if (p_cur->p_value != NULL && p_cur->control.auto_rsp == GATT_RSP_BY_STACK) {
                rsp = true;
                return rsp;
            }

        }

    }

    return rsp;

}