#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  uuid; } ;
typedef  TYPE_2__ tDIS_DB_ENTRY ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_9__ {int /*<<< orphan*/  enabled; int /*<<< orphan*/  service_handle; TYPE_2__* dis_attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  uuid16; } ;
struct TYPE_8__ {TYPE_1__ uu; } ;

/* Variables and functions */
 size_t DIS_MAX_CHAR_NUM ; 
 int /*<<< orphan*/  GATT_CHAR_PROP_BIT_READ ; 
 int /*<<< orphan*/  GATT_PERM_READ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * dis_attr_uuid ; 
 TYPE_5__ dis_cb ; 
 int dis_mask ; 
 int /*<<< orphan*/  esp_ble_gatts_add_char (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_ble_gatts_start_srvc (int /*<<< orphan*/ ) ; 
 size_t i ; 
 TYPE_3__ uuid ; 

void dis_AddChar(UINT16 service_id)
{
    //dis_cb.service_handle = service_id;
    //dis_cb.max_handle = service_id + DIS_MAX_ATTR_NUM;
    tDIS_DB_ENTRY        *p_db_attr = &dis_cb.dis_attr[0];
    while (dis_mask != 0 && i < DIS_MAX_CHAR_NUM) {
        uuid.uu.uuid16 = p_db_attr->uuid = dis_attr_uuid[i];
        esp_ble_gatts_add_char(dis_cb.service_handle, &uuid, GATT_PERM_READ,
                               GATT_CHAR_PROP_BIT_READ);
        p_db_attr ++;
        i ++;
        dis_mask >>= 1;
    }
    /*start service*/
    esp_ble_gatts_start_srvc(dis_cb.service_handle);
    dis_cb.enabled = TRUE;
}