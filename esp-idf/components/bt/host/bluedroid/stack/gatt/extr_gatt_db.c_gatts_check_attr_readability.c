#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tGATT_STATUS ;
typedef  int tGATT_SEC_FLAG ;
typedef  int tGATT_PERM ;
struct TYPE_3__ {int permission; int uuid; } ;
typedef  TYPE_1__ tGATT_ATTR16 ;
typedef  int UINT8 ;
typedef  int UINT16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int BTM_SEC_FLAG_ENCRYPTED ; 
 int GATT_ENCRYPT_KEY_SIZE_MASK ; 
 int /*<<< orphan*/  GATT_INSUF_AUTHENTICATION ; 
 int /*<<< orphan*/  GATT_INSUF_ENCRYPTION ; 
 int /*<<< orphan*/  GATT_INSUF_KEY_SIZE ; 
 int /*<<< orphan*/  GATT_NOT_LONG ; 
 int GATT_READ_ALLOWED ; 
 int GATT_READ_AUTH_REQUIRED ; 
 int GATT_READ_ENCRYPTED_REQUIRED ; 
 int GATT_READ_MITM_REQUIRED ; 
 int /*<<< orphan*/  GATT_READ_NOT_PERMIT ; 
 int GATT_SEC_FLAG_ENCRYPTED ; 
 int GATT_SEC_FLAG_LKEY_AUTHED ; 
 int GATT_SEC_FLAG_LKEY_UNAUTHED ; 
 int /*<<< orphan*/  GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
#define  GATT_UUID_CHAR_CLIENT_CONFIG 135 
#define  GATT_UUID_CHAR_DECLARE 134 
#define  GATT_UUID_CHAR_EXT_PROP 133 
#define  GATT_UUID_CHAR_PRESENT_FORMAT 132 
#define  GATT_UUID_CHAR_SRVR_CONFIG 131 
#define  GATT_UUID_INCLUDE_SERVICE 130 
#define  GATT_UUID_PRI_SERVICE 129 
#define  GATT_UUID_SEC_SERVICE 128 
 int /*<<< orphan*/  UNUSED (int) ; 

__attribute__((used)) static tGATT_STATUS gatts_check_attr_readability(tGATT_ATTR16 *p_attr,
        UINT16 offset,
        BOOLEAN read_long,
        tGATT_SEC_FLAG sec_flag,
        UINT8 key_size)
{
    UINT16          min_key_size;
    tGATT_PERM      perm = p_attr->permission;

    UNUSED(offset);
    min_key_size = (((perm & GATT_ENCRYPT_KEY_SIZE_MASK) >> 12));
    if (min_key_size != 0 ) {
        min_key_size += 6;
    }

    if (!(perm & GATT_READ_ALLOWED)) {
        GATT_TRACE_ERROR( "GATT_READ_NOT_PERMIT\n");
        return GATT_READ_NOT_PERMIT;
    }

    if ((perm & GATT_READ_AUTH_REQUIRED ) && !(sec_flag & GATT_SEC_FLAG_LKEY_UNAUTHED) &&
            !(sec_flag & BTM_SEC_FLAG_ENCRYPTED)) {
        GATT_TRACE_ERROR( "GATT_INSUF_AUTHENTICATION\n");
        return GATT_INSUF_AUTHENTICATION;
    }

    if ((perm & GATT_READ_MITM_REQUIRED ) && !(sec_flag & GATT_SEC_FLAG_LKEY_AUTHED)) {
        GATT_TRACE_ERROR( "GATT_INSUF_AUTHENTICATION: MITM Required\n");
        return GATT_INSUF_AUTHENTICATION;
    }

    if ((perm & GATT_READ_ENCRYPTED_REQUIRED ) && !(sec_flag & GATT_SEC_FLAG_ENCRYPTED)) {
        GATT_TRACE_ERROR( "GATT_INSUF_ENCRYPTION\n");
        return GATT_INSUF_ENCRYPTION;
    }

    if ( (perm & GATT_READ_ENCRYPTED_REQUIRED) && (sec_flag & GATT_SEC_FLAG_ENCRYPTED) && (key_size < min_key_size)) {
        GATT_TRACE_ERROR( "GATT_INSUF_KEY_SIZE\n");
        return GATT_INSUF_KEY_SIZE;
    }


    if (read_long) {
        switch (p_attr->uuid) {
        case GATT_UUID_PRI_SERVICE:
        case GATT_UUID_SEC_SERVICE:
        case GATT_UUID_CHAR_DECLARE:
        case GATT_UUID_INCLUDE_SERVICE:
        case GATT_UUID_CHAR_EXT_PROP:
        case GATT_UUID_CHAR_CLIENT_CONFIG:
        case GATT_UUID_CHAR_SRVR_CONFIG:
        case GATT_UUID_CHAR_PRESENT_FORMAT:
            GATT_TRACE_ERROR("GATT_NOT_LONG\n");
            return GATT_NOT_LONG;

        default:
            break;
        }
    }

    return GATT_SUCCESS;
}