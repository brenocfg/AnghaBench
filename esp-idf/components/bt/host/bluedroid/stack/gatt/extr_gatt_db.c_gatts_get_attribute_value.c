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
struct TYPE_8__ {int /*<<< orphan*/ * p_attr_list; } ;
typedef  TYPE_3__ tGATT_SVC_DB ;
typedef  int /*<<< orphan*/  tGATT_STATUS ;
struct TYPE_9__ {scalar_t__ handle; scalar_t__ uuid_type; int uuid; struct TYPE_9__* p_next; TYPE_2__* p_value; } ;
typedef  TYPE_4__ tGATT_ATTR16 ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_6__ {scalar_t__ attr_len; int /*<<< orphan*/ * attr_val; } ;
struct TYPE_7__ {TYPE_1__ attr_val; } ;

/* Variables and functions */
 scalar_t__ GATT_ATTR_UUID_TYPE_16 ; 
 int /*<<< orphan*/  GATT_INVALID_PDU ; 
 int /*<<< orphan*/  GATT_NOT_FOUND ; 
 int /*<<< orphan*/  GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,scalar_t__) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
#define  GATT_UUID_CHAR_DECLARE 129 
#define  GATT_UUID_INCLUDE_SERVICE 128 

tGATT_STATUS gatts_get_attribute_value(tGATT_SVC_DB *p_db, UINT16 attr_handle,
                                       UINT16 *length, UINT8 **value)
{
    tGATT_ATTR16  *p_cur;

    GATT_TRACE_DEBUG("attr_handle = %x\n", attr_handle);

    if (p_db == NULL) {
        GATT_TRACE_ERROR("gatts_get_attribute_value Fail:p_db is NULL.\n");
        *length = 0;
        return GATT_INVALID_PDU;
    }
    if (p_db->p_attr_list == NULL) {
        GATT_TRACE_ERROR("gatts_get_attribute_value Fail:p_db->p_attr_list is NULL.\n");
        *length = 0;
        return GATT_INVALID_PDU;
    }
    if (length == NULL){
        GATT_TRACE_ERROR("gatts_get_attribute_value Fail:length is NULL.\n");
        return GATT_INVALID_PDU;
    }
    if (value == NULL){
        GATT_TRACE_ERROR("gatts_get_attribute_value Fail:value is NULL.\n");
        *length = 0;
        return GATT_INVALID_PDU;
    }

    p_cur    =  (tGATT_ATTR16 *) p_db->p_attr_list;

    while (p_cur != NULL) {
        if (p_cur->handle == attr_handle) {

            if (p_cur->uuid_type == GATT_ATTR_UUID_TYPE_16) {
                switch (p_cur->uuid) {
                case GATT_UUID_CHAR_DECLARE:
                case GATT_UUID_INCLUDE_SERVICE:
                    break;
                default:
                    if (p_cur->p_value &&  p_cur->p_value->attr_val.attr_len != 0) {
                        *length = p_cur->p_value->attr_val.attr_len;
                        *value = p_cur->p_value->attr_val.attr_val;
                        return GATT_SUCCESS;
                    } else {
                        *length = 0;
                        return GATT_SUCCESS;
                    }
                    break;
                }
            } else {
                if (p_cur->p_value && p_cur->p_value->attr_val.attr_len != 0) {
                    *length = p_cur->p_value->attr_val.attr_len;
                    *value = p_cur->p_value->attr_val.attr_val;
                    return GATT_SUCCESS;
                } else {
                    *length = 0;
                    return GATT_SUCCESS;
                }

            }

            break;

        }

        p_cur = p_cur->p_next;
    }

    return GATT_NOT_FOUND;
}