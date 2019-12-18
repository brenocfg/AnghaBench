#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_SVC_DB ;
struct TYPE_15__ {TYPE_4__* p_value; } ;
typedef  TYPE_6__ tGATT_ATTR16 ;
struct TYPE_14__ {int /*<<< orphan*/  uuid128; int /*<<< orphan*/  uuid32; int /*<<< orphan*/  uuid16; } ;
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_16__ {scalar_t__ member_0; scalar_t__ len; TYPE_5__ uu; TYPE_1__ member_1; } ;
typedef  TYPE_7__ tBT_UUID ;
struct TYPE_11__ {int /*<<< orphan*/  uuid128; int /*<<< orphan*/  uuid16; } ;
struct TYPE_12__ {TYPE_2__ uu; void* len; } ;
struct TYPE_13__ {TYPE_3__ uuid; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GATT_PERM_READ ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  GATT_UUID_PRI_SERVICE ; 
 int /*<<< orphan*/  GATT_UUID_SEC_SERVICE ; 
 void* LEN_UUID_128 ; 
 scalar_t__ LEN_UUID_16 ; 
 scalar_t__ LEN_UUID_32 ; 
 scalar_t__ TRUE ; 
 scalar_t__ allocate_attr_in_db (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_extra_byte_in_db (int /*<<< orphan*/ *,void**,int) ; 
 int /*<<< orphan*/  gatt_convert_uuid32_to_uuid128 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static BOOLEAN gatts_db_add_service_declaration(tGATT_SVC_DB *p_db, tBT_UUID *p_service, BOOLEAN is_pri)
{
    tGATT_ATTR16  *p_attr;
    tBT_UUID    uuid = {LEN_UUID_16, {0}};
    BOOLEAN     rt = FALSE;

    GATT_TRACE_DEBUG( "add_service_declaration");

    if (is_pri) {
        uuid.uu.uuid16 = GATT_UUID_PRI_SERVICE;
    } else {
        uuid.uu.uuid16 = GATT_UUID_SEC_SERVICE;
    }

    /* add service declration record */
    if ((p_attr = (tGATT_ATTR16 *)(allocate_attr_in_db(p_db, &uuid, GATT_PERM_READ))) != NULL) {
        if (copy_extra_byte_in_db (p_db, (void **)&p_attr->p_value, sizeof(tBT_UUID))) {
            if (p_service->len == LEN_UUID_16) {
                p_attr->p_value->uuid.len = LEN_UUID_16;
                p_attr->p_value->uuid.uu.uuid16 = p_service->uu.uuid16;
            } else if (p_service->len == LEN_UUID_32) {
                p_attr->p_value->uuid.len = LEN_UUID_128;
                gatt_convert_uuid32_to_uuid128(p_attr->p_value->uuid.uu.uuid128, p_service->uu.uuid32);
            } else {
                p_attr->p_value->uuid.len = LEN_UUID_128;
                memcpy(p_attr->p_value->uuid.uu.uuid128, p_service->uu.uuid128, LEN_UUID_128);
            }
            rt = TRUE;
        }

    }
    return rt;
}