#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ tGATT_STATUS ;
typedef  int /*<<< orphan*/  tGATT_SEC_FLAG ;
struct TYPE_22__ {scalar_t__ uuid_type; int /*<<< orphan*/  uuid; } ;
typedef  TYPE_8__ tGATT_ATTR32 ;
struct TYPE_19__ {scalar_t__ auto_rsp; } ;
struct TYPE_23__ {scalar_t__ uuid; scalar_t__ uuid_type; TYPE_7__* p_value; TYPE_5__ control; scalar_t__ p_next; int /*<<< orphan*/  permission; } ;
typedef  TYPE_9__ tGATT_ATTR16 ;
struct TYPE_13__ {int /*<<< orphan*/ * uuid; } ;
typedef  TYPE_10__ tGATT_ATTR128 ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_20__ {scalar_t__ attr_len; int /*<<< orphan*/ * attr_val; } ;
struct TYPE_16__ {scalar_t__ uuid16; } ;
struct TYPE_17__ {scalar_t__ len; TYPE_2__ uu; } ;
struct TYPE_18__ {scalar_t__ s_handle; scalar_t__ e_handle; TYPE_3__ service_type; } ;
struct TYPE_15__ {scalar_t__ char_val_handle; int /*<<< orphan*/  property; } ;
struct TYPE_14__ {scalar_t__ len; } ;
struct TYPE_21__ {TYPE_6__ attr_val; TYPE_4__ incl_handle; TYPE_1__ char_decl; TYPE_12__ uuid; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ GATT_ATTR_UUID_TYPE_16 ; 
 scalar_t__ GATT_ATTR_UUID_TYPE_32 ; 
 scalar_t__ GATT_INVALID_OFFSET ; 
 scalar_t__ GATT_NO_RESOURCES ; 
 scalar_t__ GATT_PENDING ; 
 scalar_t__ GATT_RSP_BY_STACK ; 
 scalar_t__ GATT_STACK_RSP ; 
 scalar_t__ GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GATT_UNKNOWN_ERROR ; 
 scalar_t__ GATT_UUID_CHAR_DECLARE ; 
 scalar_t__ GATT_UUID_INCLUDE_SERVICE ; 
 scalar_t__ GATT_UUID_PRI_SERVICE ; 
 scalar_t__ GATT_UUID_SEC_SERVICE ; 
 scalar_t__ LEN_UUID_128 ; 
 scalar_t__ LEN_UUID_16 ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gatt_build_uuid_to_stream (int /*<<< orphan*/ **,TYPE_12__) ; 
 int /*<<< orphan*/  gatt_convert_uuid32_to_uuid128 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gatts_check_attr_readability (TYPE_9__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tGATT_STATUS read_attr_value (void *p_attr,
                                     UINT16 offset,
                                     UINT8 **p_data,
                                     BOOLEAN read_long,
                                     UINT16 mtu,
                                     UINT16 *p_len,
                                     tGATT_SEC_FLAG sec_flag,
                                     UINT8 key_size)
{
    UINT16          len = 0, uuid16 = 0;
    UINT8           *p = *p_data;
    tGATT_STATUS    status;
    tGATT_ATTR16    *p_attr16  = (tGATT_ATTR16 *)p_attr;

    GATT_TRACE_DEBUG("read_attr_value uuid=0x%04x perm=0x%0x sec_flag=0x%x offset=%d read_long=%d\n",
                     p_attr16->uuid,
                     p_attr16->permission,
                     sec_flag,
                     offset,
                     read_long);

    status = gatts_check_attr_readability((tGATT_ATTR16 *)p_attr, offset, read_long, sec_flag, key_size);

    if (status != GATT_SUCCESS) {
        return status;
    }

    if (p_attr16->uuid_type == GATT_ATTR_UUID_TYPE_16) {
        uuid16 = p_attr16->uuid;
    }

    status = GATT_NO_RESOURCES;

    if (uuid16 == GATT_UUID_PRI_SERVICE || uuid16 == GATT_UUID_SEC_SERVICE) {
        len = p_attr16->p_value->uuid.len;
        if (mtu >= p_attr16->p_value->uuid.len) {
            gatt_build_uuid_to_stream(&p, p_attr16->p_value->uuid);
            status = GATT_SUCCESS;
        }
    } else if (uuid16 == GATT_UUID_CHAR_DECLARE) {
        len = (((tGATT_ATTR16 *)(p_attr16->p_next))->uuid_type == GATT_ATTR_UUID_TYPE_16) ? 5 : 19;

        if (mtu >= len) {
            UINT8_TO_STREAM(p, p_attr16->p_value->char_decl.property);
            UINT16_TO_STREAM(p, p_attr16->p_value->char_decl.char_val_handle);

            if (((tGATT_ATTR16 *)(p_attr16->p_next))->uuid_type == GATT_ATTR_UUID_TYPE_16) {
                UINT16_TO_STREAM(p, ((tGATT_ATTR16 *)(p_attr16->p_next))->uuid);
            }
            /* convert a 32bits UUID to 128 bits */
            else if (((tGATT_ATTR32 *)(p_attr16->p_next))->uuid_type == GATT_ATTR_UUID_TYPE_32) {
                gatt_convert_uuid32_to_uuid128 (p, ((tGATT_ATTR32 *)(p_attr16->p_next))->uuid);
                p += LEN_UUID_128;
            } else {
                ARRAY_TO_STREAM (p, ((tGATT_ATTR128 *)(p_attr16->p_next))->uuid, LEN_UUID_128);
            }
            status = GATT_SUCCESS;
        }

    } else if (uuid16 == GATT_UUID_INCLUDE_SERVICE) {
        if (p_attr16->p_value->incl_handle.service_type.len == LEN_UUID_16) {
            len = 6;
        } else {
            len = 4;
        }

        if (mtu >= len) {
            UINT16_TO_STREAM(p, p_attr16->p_value->incl_handle.s_handle);
            UINT16_TO_STREAM(p, p_attr16->p_value->incl_handle.e_handle);

            if (p_attr16->p_value->incl_handle.service_type.len == LEN_UUID_16) {
                UINT16_TO_STREAM(p, p_attr16->p_value->incl_handle.service_type.uu.uuid16);
            }
            status = GATT_SUCCESS;
        }
    } else { /* characteristic description or characteristic value */
        if (p_attr16->control.auto_rsp == GATT_RSP_BY_STACK) {
            if (p_attr16->p_value == NULL || p_attr16->p_value->attr_val.attr_val == NULL) {
                status = GATT_UNKNOWN_ERROR;
            }
            else if (offset > p_attr16->p_value->attr_val.attr_len){
			/*if offset equal to max_len, should respond with zero byte value
            //if offset is greater than max_len, should respond with an error*/
                status = GATT_INVALID_OFFSET;
            } else { 
                UINT8 *value = (UINT8 *)(p_attr16->p_value->attr_val.attr_val) + offset;
                UINT16 len_left = p_attr16->p_value->attr_val.attr_len - offset;
                len = (mtu >= len_left) ? (len_left) : mtu;
                ARRAY_TO_STREAM(p, value, len);
                status = GATT_STACK_RSP;
            }

        } else {
            status = GATT_PENDING;
        }
    }

    *p_len = len;
    *p_data = p;
    return status;
}