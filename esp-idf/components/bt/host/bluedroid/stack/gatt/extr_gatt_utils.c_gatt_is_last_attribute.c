#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  p_db; } ;
typedef  TYPE_1__ tGATT_SR_REG ;
struct TYPE_8__ {int /*<<< orphan*/ * p_last_primary; } ;
typedef  TYPE_2__ tGATT_SRV_LIST_INFO ;
struct TYPE_9__ {struct TYPE_9__* p_next; int /*<<< orphan*/  i_sreg; } ;
typedef  TYPE_3__ tGATT_SRV_LIST_ELEM ;
typedef  int /*<<< orphan*/  tBT_UUID ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* GATT_GET_SR_REG_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ gatt_uuid_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gatts_get_service_uuid (int /*<<< orphan*/ ) ; 

BOOLEAN gatt_is_last_attribute(tGATT_SRV_LIST_INFO *p_list, tGATT_SRV_LIST_ELEM *p_start, tBT_UUID value)
{
    tGATT_SRV_LIST_ELEM *p_srv = p_start->p_next;
    BOOLEAN              is_last_attribute = TRUE;
    tGATT_SR_REG        *p_rcb = NULL;
    tBT_UUID            *p_svc_uuid;

    p_list->p_last_primary = NULL;

    while (p_srv) {
        p_rcb = GATT_GET_SR_REG_PTR(p_srv->i_sreg);

        p_svc_uuid = gatts_get_service_uuid (p_rcb->p_db);

        if (gatt_uuid_compare(value, *p_svc_uuid)) {
            is_last_attribute = FALSE;
            break;

        }
        p_srv = p_srv->p_next;
    }

    return is_last_attribute;

}