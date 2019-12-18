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
struct TYPE_6__ {scalar_t__ primary_record; char* client_executable_url; char* service_description; char* documentation_url; scalar_t__ vendor; scalar_t__ product; scalar_t__ version; scalar_t__ vendor_id_source; } ;
typedef  TYPE_2__ tSDP_DI_RECORD ;
typedef  int /*<<< orphan*/  di_specid ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_5__ {scalar_t__ di_primary_handle; } ;
struct TYPE_7__ {TYPE_1__ server_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ID_CLIENT_EXE_URL ; 
 int /*<<< orphan*/  ATTR_ID_DOCUMENTATION_URL ; 
 int /*<<< orphan*/  ATTR_ID_PRIMARY_RECORD ; 
 int /*<<< orphan*/  ATTR_ID_PRODUCT_ID ; 
 int /*<<< orphan*/  ATTR_ID_PRODUCT_VERSION ; 
 int /*<<< orphan*/  ATTR_ID_SERVICE_DESCRIPTION ; 
 int /*<<< orphan*/  ATTR_ID_SPECIFICATION_ID ; 
 int /*<<< orphan*/  ATTR_ID_VENDOR_ID ; 
 int /*<<< orphan*/  ATTR_ID_VENDOR_ID_SOURCE ; 
 scalar_t__ BLUETOOTH_DI_SPECIFICATION ; 
 int /*<<< orphan*/  BOOLEAN_DESC_TYPE ; 
 scalar_t__ FALSE ; 
 scalar_t__ SDP_AddAttribute (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ SDP_AddServiceClassIdList (scalar_t__,int,scalar_t__*) ; 
 scalar_t__ SDP_CreateRecord () ; 
 scalar_t__ SDP_DI_REG_FAILED ; 
 int /*<<< orphan*/  SDP_DeleteRecord (scalar_t__) ; 
 scalar_t__ SDP_ILLEGAL_PARAMETER ; 
 scalar_t__ SDP_MAX_ATTR_LEN ; 
 scalar_t__ SDP_NO_RESOURCES ; 
 scalar_t__ SDP_SUCCESS ; 
 int /*<<< orphan*/  TEXT_STR_DESC_TYPE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UINT16_TO_BE_STREAM (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  UINT_DESC_TYPE ; 
 int /*<<< orphan*/  URL_DESC_TYPE ; 
 scalar_t__ UUID_SERVCLASS_PNP_INFORMATION ; 
 TYPE_3__ sdp_cb ; 
 scalar_t__ strlen (char*) ; 

UINT16 SDP_SetLocalDiRecord( tSDP_DI_RECORD *p_device_info, UINT32 *p_handle )
{
#if SDP_SERVER_ENABLED == TRUE
    UINT16  result = SDP_SUCCESS;
    UINT32  handle;
    UINT16  di_uuid = UUID_SERVCLASS_PNP_INFORMATION;
    UINT16  di_specid = BLUETOOTH_DI_SPECIFICATION;
    UINT8   temp_u16[2];
    UINT8   *p_temp;
    UINT8   u8;

    *p_handle = 0;
    if ( p_device_info == NULL ) {
        return SDP_ILLEGAL_PARAMETER;
    }

    /* if record is to be primary record, get handle to replace old primary */
    if ( p_device_info->primary_record == TRUE && sdp_cb.server_db.di_primary_handle ) {
        handle = sdp_cb.server_db.di_primary_handle;
    } else {
        if ( (handle = SDP_CreateRecord()) == 0 ) {
            return SDP_NO_RESOURCES;
        }
    }

    *p_handle = handle;

    /* build the SDP entry */
    /* Add the UUID to the Service Class ID List */
    if ((SDP_AddServiceClassIdList(handle, 1, &di_uuid)) == FALSE) {
        result = SDP_DI_REG_FAILED;
    }

    /* mandatory */
    if ( result == SDP_SUCCESS) {
        p_temp = temp_u16;
        UINT16_TO_BE_STREAM(p_temp, di_specid);
        if ( !(SDP_AddAttribute(handle, ATTR_ID_SPECIFICATION_ID,
                                UINT_DESC_TYPE, sizeof(di_specid),
                                temp_u16)) ) {
            result = SDP_DI_REG_FAILED;
        }
    }

    /* optional - if string is null, do not add attribute */
    if ( result == SDP_SUCCESS ) {
        if ( p_device_info->client_executable_url[0] != '\0' ) {
            if ( !((strlen(p_device_info->client_executable_url) + 1 <= SDP_MAX_ATTR_LEN) &&
                    SDP_AddAttribute(handle, ATTR_ID_CLIENT_EXE_URL, URL_DESC_TYPE,
                                     (UINT32)(strlen(p_device_info->client_executable_url) + 1),
                                     (UINT8 *)p_device_info->client_executable_url)) ) {
                result = SDP_DI_REG_FAILED;
            }
        }
    }

    /* optional - if string is null, do not add attribute */
    if ( result == SDP_SUCCESS ) {
        if ( p_device_info->service_description[0] != '\0' ) {
            if ( !((strlen(p_device_info->service_description) + 1 <= SDP_MAX_ATTR_LEN) &&
                    SDP_AddAttribute(handle, ATTR_ID_SERVICE_DESCRIPTION,
                                     TEXT_STR_DESC_TYPE,
                                     (UINT32)(strlen(p_device_info->service_description) + 1),
                                     (UINT8 *)p_device_info->service_description)) ) {
                result = SDP_DI_REG_FAILED;
            }
        }
    }

    /* optional - if string is null, do not add attribute */
    if ( result == SDP_SUCCESS ) {
        if ( p_device_info->documentation_url[0] != '\0' ) {
            if ( !((strlen(p_device_info->documentation_url) + 1 <= SDP_MAX_ATTR_LEN) &&
                    SDP_AddAttribute(handle, ATTR_ID_DOCUMENTATION_URL, URL_DESC_TYPE,
                                     (UINT32)(strlen(p_device_info->documentation_url) + 1),
                                     (UINT8 *)p_device_info->documentation_url)) ) {
                result = SDP_DI_REG_FAILED;
            }
        }
    }

    /* mandatory */
    if ( result == SDP_SUCCESS) {
        p_temp = temp_u16;
        UINT16_TO_BE_STREAM(p_temp, p_device_info->vendor);
        if ( !(SDP_AddAttribute(handle, ATTR_ID_VENDOR_ID, UINT_DESC_TYPE,
                                sizeof(p_device_info->vendor), temp_u16)) ) {
            result = SDP_DI_REG_FAILED;
        }
    }

    /* mandatory */
    if ( result == SDP_SUCCESS) {
        p_temp = temp_u16;
        UINT16_TO_BE_STREAM (p_temp, p_device_info->product);
        if ( !(SDP_AddAttribute(handle, ATTR_ID_PRODUCT_ID,
                                UINT_DESC_TYPE, sizeof(p_device_info->product), temp_u16)) ) {
            result = SDP_DI_REG_FAILED;
        }
    }

    /* mandatory */
    if ( result == SDP_SUCCESS) {
        p_temp = temp_u16;
        UINT16_TO_BE_STREAM (p_temp, p_device_info->version);
        if ( !(SDP_AddAttribute(handle, ATTR_ID_PRODUCT_VERSION, UINT_DESC_TYPE,
                                sizeof(p_device_info->version), temp_u16)) ) {
            result = SDP_DI_REG_FAILED;
        }
    }

    /* mandatory */
    if ( result == SDP_SUCCESS) {
        u8 = (UINT8)p_device_info->primary_record;
        if ( !(SDP_AddAttribute(handle, ATTR_ID_PRIMARY_RECORD,
                                BOOLEAN_DESC_TYPE, 1, &u8)) ) {
            result = SDP_DI_REG_FAILED;
        }
    }

    /* mandatory */
    if ( result == SDP_SUCCESS) {
        p_temp = temp_u16;
        UINT16_TO_BE_STREAM(p_temp, p_device_info->vendor_id_source);
        if ( !(SDP_AddAttribute(handle, ATTR_ID_VENDOR_ID_SOURCE, UINT_DESC_TYPE,
                                sizeof(p_device_info->vendor_id_source), temp_u16)) ) {
            result = SDP_DI_REG_FAILED;
        }
    }

    if ( result != SDP_SUCCESS ) {
        SDP_DeleteRecord( handle );
    } else if (p_device_info->primary_record == TRUE) {
        sdp_cb.server_db.di_primary_handle = handle;
    }

    return result;
#else   /* SDP_SERVER_ENABLED is FALSE */
    return SDP_DI_REG_FAILED;
#endif  /* if SDP_SERVER_ENABLED */
}