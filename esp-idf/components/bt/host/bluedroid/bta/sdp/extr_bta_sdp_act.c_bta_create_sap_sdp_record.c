#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * params; } ;
typedef  TYPE_5__ tSDP_PROTOCOL_ELEM ;
typedef  int /*<<< orphan*/  tSDP_DISC_REC ;
struct TYPE_11__ {scalar_t__ array; } ;
struct TYPE_12__ {TYPE_1__ v; } ;
struct TYPE_16__ {TYPE_2__ attr_value; int /*<<< orphan*/  attr_len_type; } ;
typedef  TYPE_6__ tSDP_DISC_ATTR ;
struct TYPE_13__ {char* service_name; int l2cap_psm; int profile_version; int /*<<< orphan*/  rfcomm_channel_number; int /*<<< orphan*/  service_name_length; int /*<<< orphan*/  type; } ;
struct TYPE_14__ {TYPE_3__ hdr; } ;
struct TYPE_17__ {TYPE_4__ sap; } ;
typedef  TYPE_7__ bluetooth_sdp_record ;
typedef  int UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ID_SERVICE_NAME ; 
 int /*<<< orphan*/  SDP_DISC_ATTR_LEN (int /*<<< orphan*/ ) ; 
 TYPE_6__* SDP_FindAttributeInRec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SDP_FindProfileVersionInRec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ SDP_FindProtocolListElemInRec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  SDP_TYPE_MAP_MAS ; 
 int /*<<< orphan*/  UUID_PROTOCOL_RFCOMM ; 
 int /*<<< orphan*/  UUID_SERVCLASS_SAP ; 

__attribute__((used)) static void bta_create_sap_sdp_record(bluetooth_sdp_record *record, tSDP_DISC_REC *p_rec)
{
    tSDP_DISC_ATTR *p_attr;
    tSDP_PROTOCOL_ELEM pe;
    UINT16 pversion = -1;

    record->sap.hdr.type = SDP_TYPE_MAP_MAS;
    record->sap.hdr.service_name_length = 0;
    record->sap.hdr.service_name = NULL;
    record->sap.hdr.rfcomm_channel_number = 0;
    record->sap.hdr.l2cap_psm = -1;
    record->sap.hdr.profile_version = 0;

    if ((p_attr = SDP_FindAttributeInRec(p_rec, ATTR_ID_SERVICE_NAME)) != NULL) {
        record->sap.hdr.service_name_length = SDP_DISC_ATTR_LEN(p_attr->attr_len_type);
        record->sap.hdr.service_name = (char *)p_attr->attr_value.v.array;
    }

    if (SDP_FindProfileVersionInRec(p_rec, UUID_SERVCLASS_SAP, &pversion)) {
        record->sap.hdr.profile_version = pversion;
    }

    if (SDP_FindProtocolListElemInRec(p_rec, UUID_PROTOCOL_RFCOMM, &pe)) {
        record->sap.hdr.rfcomm_channel_number = pe.params[0];
    }
}