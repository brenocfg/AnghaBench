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
struct TYPE_4__ {scalar_t__ p_attr_list; } ;
typedef  TYPE_1__ tGATT_SVC_DB ;
typedef  int /*<<< orphan*/  tGATT_STATUS ;
typedef  int tGATT_SEC_FLAG ;
typedef  int tGATT_PERM ;
struct TYPE_5__ {scalar_t__ handle; int permission; scalar_t__ uuid_type; int uuid; scalar_t__ p_next; } ;
typedef  TYPE_2__ tGATT_ATTR16 ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */
 scalar_t__ GATT_ATTR_UUID_TYPE_128 ; 
 scalar_t__ GATT_ATTR_UUID_TYPE_16 ; 
 scalar_t__ GATT_ATTR_UUID_TYPE_32 ; 
 scalar_t__ GATT_CMD_WRITE ; 
 int GATT_ENCRYPT_KEY_SIZE_MASK ; 
 int /*<<< orphan*/  GATT_INSUF_AUTHENTICATION ; 
 int /*<<< orphan*/  GATT_INSUF_ENCRYPTION ; 
 int /*<<< orphan*/  GATT_INSUF_KEY_SIZE ; 
 int /*<<< orphan*/  GATT_INVALID_ATTR_LEN ; 
 int /*<<< orphan*/  GATT_INVALID_PDU ; 
 int /*<<< orphan*/  GATT_NOT_FOUND ; 
 int /*<<< orphan*/  GATT_NOT_LONG ; 
 int GATT_PERM_WRITE_ENCRYPTED ; 
 int GATT_PERM_WRITE_ENC_MITM ; 
 int GATT_PERM_WRITE_SIGNED ; 
 int GATT_PERM_WRITE_SIGNED_MITM ; 
 scalar_t__ GATT_REQ_PREPARE_WRITE ; 
 scalar_t__ GATT_REQ_WRITE ; 
 int GATT_SEC_FLAG_ENCRYPTED ; 
 int GATT_SEC_FLAG_LKEY_AUTHED ; 
 int GATT_SEC_FLAG_LKEY_UNAUTHED ; 
 scalar_t__ GATT_SIGN_CMD_WRITE ; 
 int /*<<< orphan*/  GATT_SUCCESS ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*) ; 
#define  GATT_UUID_CHAR_AGG_FORMAT 134 
#define  GATT_UUID_CHAR_CLIENT_CONFIG 133 
#define  GATT_UUID_CHAR_DESCRIPTION 132 
#define  GATT_UUID_CHAR_EXT_PROP 131 
#define  GATT_UUID_CHAR_PRESENT_FORMAT 130 
#define  GATT_UUID_CHAR_SRVR_CONFIG 129 
#define  GATT_UUID_CHAR_VALID_RANGE 128 
 int GATT_WRITE_ALLOWED ; 
 int GATT_WRITE_AUTH_REQUIRED ; 
 int GATT_WRITE_ENCRYPTED_PERM ; 
 int GATT_WRITE_MITM_REQUIRED ; 
 int /*<<< orphan*/  GATT_WRITE_NOT_PERMIT ; 
 int GATT_WRITE_SIGNED_PERM ; 

tGATT_STATUS gatts_write_attr_perm_check (tGATT_SVC_DB *p_db, UINT8 op_code,
        UINT16 handle, UINT16 offset, UINT8 *p_data,
        UINT16 len, tGATT_SEC_FLAG sec_flag, UINT8 key_size)
{
    tGATT_STATUS    status = GATT_NOT_FOUND;
    tGATT_ATTR16    *p_attr;
    UINT16          max_size = 0;
    tGATT_PERM      perm;
    UINT16          min_key_size;

    GATT_TRACE_DEBUG( "gatts_write_attr_perm_check op_code=0x%0x handle=0x%04x offset=%d len=%d sec_flag=0x%0x key_size=%d",
                      op_code, handle, offset, len, sec_flag, key_size);

    if (p_db != NULL) {
        p_attr = (tGATT_ATTR16 *) p_db->p_attr_list;

        while (p_attr != NULL) {
            if (p_attr->handle == handle) {
                perm = p_attr->permission;
                min_key_size = (((perm & GATT_ENCRYPT_KEY_SIZE_MASK) >> 12));
                if (min_key_size != 0 ) {
                    min_key_size += 6;
                }
                GATT_TRACE_DEBUG( "gatts_write_attr_perm_check p_attr->permission =0x%04x min_key_size==0x%04x",
                                  p_attr->permission,
                                  min_key_size);

                if ((op_code == GATT_CMD_WRITE || op_code == GATT_REQ_WRITE)
                        && (perm & GATT_WRITE_SIGNED_PERM)) {
                    /* use the rules for the mixed security see section 10.2.3*/
                    /* use security mode 1 level 2 when the following condition follows */
                    /* LE security mode 2 level 1 and LE security mode 1 level 2 */
                    if ((perm & GATT_PERM_WRITE_SIGNED) && (perm & GATT_PERM_WRITE_ENCRYPTED)) {
                        perm = GATT_PERM_WRITE_ENCRYPTED;
                    }
                    /* use security mode 1 level 3 when the following condition follows */
                    /* LE security mode 2 level 2 and security mode 1 and LE */
                    else if (((perm & GATT_PERM_WRITE_SIGNED_MITM) && (perm & GATT_PERM_WRITE_ENCRYPTED)) ||
                             /* LE security mode 2 and security mode 1 level 3 */
                             ((perm & GATT_WRITE_SIGNED_PERM) && (perm & GATT_PERM_WRITE_ENC_MITM))) {
                        perm = GATT_PERM_WRITE_ENC_MITM;
                    }
                }

                if ((op_code == GATT_SIGN_CMD_WRITE) && !(perm & GATT_WRITE_SIGNED_PERM)) {
                    status = GATT_WRITE_NOT_PERMIT;
                    GATT_TRACE_DEBUG( "gatts_write_attr_perm_check - sign cmd write not allowed");
                }
                if ((op_code == GATT_SIGN_CMD_WRITE) && (sec_flag & GATT_SEC_FLAG_ENCRYPTED)) {
                    status = GATT_INVALID_PDU;
                    GATT_TRACE_ERROR( "gatts_write_attr_perm_check - Error!! sign cmd write sent on a encypted link");
                } else if (!(perm & GATT_WRITE_ALLOWED)) {
                    status = GATT_WRITE_NOT_PERMIT;
                    GATT_TRACE_ERROR( "gatts_write_attr_perm_check - GATT_WRITE_NOT_PERMIT");
                }
                /* require authentication, but not been authenticated */
                else if ((perm & GATT_WRITE_AUTH_REQUIRED ) && !(sec_flag & GATT_SEC_FLAG_LKEY_UNAUTHED)) {
                    status = GATT_INSUF_AUTHENTICATION;
                    GATT_TRACE_ERROR( "gatts_write_attr_perm_check - GATT_INSUF_AUTHENTICATION");
                } else if ((perm & GATT_WRITE_MITM_REQUIRED ) && !(sec_flag & GATT_SEC_FLAG_LKEY_AUTHED)) {
                    status = GATT_INSUF_AUTHENTICATION;
                    GATT_TRACE_ERROR( "gatts_write_attr_perm_check - GATT_INSUF_AUTHENTICATION: MITM required");
                } else if ((perm & GATT_WRITE_ENCRYPTED_PERM ) && !(sec_flag & GATT_SEC_FLAG_ENCRYPTED)) {
                    status = GATT_INSUF_ENCRYPTION;
                    GATT_TRACE_ERROR( "gatts_write_attr_perm_check - GATT_INSUF_ENCRYPTION");
                } else if ((perm & GATT_WRITE_ENCRYPTED_PERM ) && (sec_flag & GATT_SEC_FLAG_ENCRYPTED) && (key_size < min_key_size)) {
                    status = GATT_INSUF_KEY_SIZE;
                    GATT_TRACE_ERROR( "gatts_write_attr_perm_check - GATT_INSUF_KEY_SIZE");
                }
                /* LE security mode 2 attribute  */
                else if (perm & GATT_WRITE_SIGNED_PERM && op_code != GATT_SIGN_CMD_WRITE && !(sec_flag & GATT_SEC_FLAG_ENCRYPTED)
                         &&  (perm & GATT_WRITE_ALLOWED) == 0) {
                    status = GATT_INSUF_AUTHENTICATION;
                    GATT_TRACE_ERROR( "gatts_write_attr_perm_check - GATT_INSUF_AUTHENTICATION: LE security mode 2 required");
                } else { /* writable: must be char value declaration or char descritpors */
                    if (p_attr->uuid_type == GATT_ATTR_UUID_TYPE_16) {
                        switch (p_attr->uuid) {
                        case GATT_UUID_CHAR_PRESENT_FORMAT:/* should be readable only */
                        case GATT_UUID_CHAR_EXT_PROP:/* should be readable only */
                        case GATT_UUID_CHAR_AGG_FORMAT: /* should be readable only */
                        case GATT_UUID_CHAR_VALID_RANGE:
                            status = GATT_WRITE_NOT_PERMIT;
                            break;

                        case GATT_UUID_CHAR_CLIENT_CONFIG:
                        /* coverity[MISSING_BREAK] */
                        /* intnended fall through, ignored */
                        /* fall through */
                        case GATT_UUID_CHAR_SRVR_CONFIG:
                            max_size = 2;
                        case GATT_UUID_CHAR_DESCRIPTION:
                        default: /* any other must be character value declaration */
                            status = GATT_SUCCESS;
                            break;
                        }
                    } else if (p_attr->uuid_type == GATT_ATTR_UUID_TYPE_128 ||
                               p_attr->uuid_type == GATT_ATTR_UUID_TYPE_32) {
                        status = GATT_SUCCESS;
                    } else {
                        status = GATT_INVALID_PDU;
                    }

                    if (p_data == NULL && len  > 0) {
                        status = GATT_INVALID_PDU;
                    }
                    /* these attribute does not allow write blob */
// btla-specific ++
                    else if ( (p_attr->uuid_type == GATT_ATTR_UUID_TYPE_16) &&
                              (p_attr->uuid == GATT_UUID_CHAR_CLIENT_CONFIG ||
                               p_attr->uuid == GATT_UUID_CHAR_SRVR_CONFIG) )
// btla-specific --
                    {
                        if (op_code == GATT_REQ_PREPARE_WRITE && offset != 0) { /* does not allow write blob */
                            status = GATT_NOT_LONG;
                            GATT_TRACE_ERROR( "gatts_write_attr_perm_check - GATT_NOT_LONG");
                        } else if (len != max_size) { /* data does not match the required format */
                            status = GATT_INVALID_ATTR_LEN;
                            GATT_TRACE_ERROR( "gatts_write_attr_perm_check - GATT_INVALID_PDU");
                        } else {
                            status = GATT_SUCCESS;
                        }
                    }
                }
                break;
            } else {
                p_attr = (tGATT_ATTR16 *)p_attr->p_next;
            }
        }
    }

    return status;
}