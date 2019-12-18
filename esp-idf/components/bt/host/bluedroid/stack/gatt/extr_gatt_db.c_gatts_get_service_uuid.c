#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ p_attr_list; } ;
typedef  TYPE_2__ tGATT_SVC_DB ;
struct TYPE_7__ {TYPE_1__* p_value; } ;
typedef  TYPE_3__ tGATT_ATTR16 ;
typedef  int /*<<< orphan*/  tBT_UUID ;
struct TYPE_5__ {int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 

tBT_UUID *gatts_get_service_uuid (tGATT_SVC_DB *p_db)
{
    if (!p_db || !p_db->p_attr_list) {
        GATT_TRACE_ERROR("service DB empty\n");

        return NULL;
    } else {
        return &((tGATT_ATTR16 *)p_db->p_attr_list)->p_value->uuid;
    }
}