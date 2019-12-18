#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ primary_record; int /*<<< orphan*/  version; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor_id_source; int /*<<< orphan*/  vendor; int /*<<< orphan*/  documentation_url; int /*<<< orphan*/  service_description; int /*<<< orphan*/  client_executable_url; } ;
struct TYPE_12__ {TYPE_1__ rec; int /*<<< orphan*/  spec_id; } ;
typedef  TYPE_4__ tSDP_DI_GET_RECORD ;
typedef  int /*<<< orphan*/  tSDP_DISC_REC ;
struct TYPE_10__ {scalar_t__ u8; int /*<<< orphan*/  u16; } ;
struct TYPE_11__ {TYPE_2__ v; } ;
struct TYPE_13__ {TYPE_3__ attr_value; } ;
typedef  TYPE_5__ tSDP_DISC_ATTR ;
typedef  int /*<<< orphan*/  tSDP_DISCOVERY_DB ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT16 ;
typedef  scalar_t__ BOOLEAN ;

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
 int /*<<< orphan*/  SDP_AttrStringCopy (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SDP_ERR_ATTR_NOT_PRESENT ; 
 TYPE_5__* SDP_FindAttributeInRec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SDP_FindServiceInDb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDP_MAX_ATTR_LEN ; 
 scalar_t__ SDP_NO_DI_RECORD_FOUND ; 
 scalar_t__ SDP_SUCCESS ; 
 int /*<<< orphan*/  UUID_SERVCLASS_PNP_INFORMATION ; 

UINT16 SDP_GetDiRecord( UINT8 get_record_index, tSDP_DI_GET_RECORD *p_device_info,
                        tSDP_DISCOVERY_DB *p_db )
{
#if SDP_CLIENT_ENABLED == TRUE
    UINT16  result = SDP_NO_DI_RECORD_FOUND;
    UINT8  curr_record_index = 1;

    tSDP_DISC_REC *p_curr_record = NULL;

    /* find the requested SDP record in the discovery database */
    do {
        p_curr_record = SDP_FindServiceInDb( p_db, UUID_SERVCLASS_PNP_INFORMATION,
                                             p_curr_record );
        if ( p_curr_record ) {
            if ( curr_record_index++ == get_record_index ) {
                result = SDP_SUCCESS;
                break;
            }
        }
    } while ( p_curr_record );

    if ( result == SDP_SUCCESS ) {
        /* copy the information from the SDP record to the DI record */
        tSDP_DISC_ATTR *p_curr_attr = NULL;

        /* ClientExecutableURL is optional */
        p_curr_attr = SDP_FindAttributeInRec( p_curr_record, ATTR_ID_CLIENT_EXE_URL );
        SDP_AttrStringCopy( p_device_info->rec.client_executable_url, p_curr_attr,
                            SDP_MAX_ATTR_LEN );

        /* Service Description is optional */
        p_curr_attr = SDP_FindAttributeInRec( p_curr_record, ATTR_ID_SERVICE_DESCRIPTION );
        SDP_AttrStringCopy( p_device_info->rec.service_description, p_curr_attr, SDP_MAX_ATTR_LEN );

        /* DocumentationURL is optional */
        p_curr_attr = SDP_FindAttributeInRec( p_curr_record, ATTR_ID_DOCUMENTATION_URL );
        SDP_AttrStringCopy( p_device_info->rec.documentation_url, p_curr_attr, SDP_MAX_ATTR_LEN );

        p_curr_attr = SDP_FindAttributeInRec( p_curr_record, ATTR_ID_SPECIFICATION_ID );
        if ( p_curr_attr ) {
            p_device_info->spec_id = p_curr_attr->attr_value.v.u16;
        } else {
            result = SDP_ERR_ATTR_NOT_PRESENT;
        }

        p_curr_attr = SDP_FindAttributeInRec( p_curr_record, ATTR_ID_VENDOR_ID );
        if ( p_curr_attr ) {
            p_device_info->rec.vendor = p_curr_attr->attr_value.v.u16;
        } else {
            result = SDP_ERR_ATTR_NOT_PRESENT;
        }

        p_curr_attr = SDP_FindAttributeInRec( p_curr_record, ATTR_ID_VENDOR_ID_SOURCE );
        if ( p_curr_attr ) {
            p_device_info->rec.vendor_id_source = p_curr_attr->attr_value.v.u16;
        } else {
            result = SDP_ERR_ATTR_NOT_PRESENT;
        }

        p_curr_attr = SDP_FindAttributeInRec( p_curr_record, ATTR_ID_PRODUCT_ID );
        if ( p_curr_attr ) {
            p_device_info->rec.product = p_curr_attr->attr_value.v.u16;
        } else {
            result = SDP_ERR_ATTR_NOT_PRESENT;
        }

        p_curr_attr = SDP_FindAttributeInRec( p_curr_record, ATTR_ID_PRODUCT_VERSION );
        if ( p_curr_attr ) {
            p_device_info->rec.version = p_curr_attr->attr_value.v.u16;
        } else {
            result = SDP_ERR_ATTR_NOT_PRESENT;
        }

        p_curr_attr = SDP_FindAttributeInRec( p_curr_record, ATTR_ID_PRIMARY_RECORD );
        if ( p_curr_attr ) {
            p_device_info->rec.primary_record = (BOOLEAN)p_curr_attr->attr_value.v.u8;
        } else {
            result = SDP_ERR_ATTR_NOT_PRESENT;
        }
    }

    return result;
#else   /* SDP_CLIENT_ENABLED is FALSE */
    return SDP_NO_DI_RECORD_FOUND;
#endif
}