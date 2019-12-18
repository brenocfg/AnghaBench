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
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/ * params; } ;
typedef  TYPE_7__ tSDP_PROTOCOL_ELEM ;
typedef  int /*<<< orphan*/  tSDP_DISC_REC ;
struct TYPE_15__ {scalar_t__ array; } ;
struct TYPE_16__ {TYPE_1__ v; } ;
struct TYPE_22__ {TYPE_2__ attr_value; int /*<<< orphan*/  attr_len_type; } ;
typedef  TYPE_8__ tSDP_DISC_ATTR ;
struct TYPE_19__ {int rfcomm_channel_number; int l2cap_psm; int profile_version; int /*<<< orphan*/  user1_ptr; int /*<<< orphan*/  user1_ptr_len; int /*<<< orphan*/ * service_name; scalar_t__ service_name_length; int /*<<< orphan*/  type; } ;
struct TYPE_17__ {char* service_name; int /*<<< orphan*/  rfcomm_channel_number; int /*<<< orphan*/  service_name_length; } ;
struct TYPE_18__ {TYPE_3__ hdr; } ;
struct TYPE_23__ {TYPE_5__ hdr; TYPE_4__ pse; } ;
typedef  TYPE_9__ bluetooth_sdp_record ;
struct TYPE_20__ {int /*<<< orphan*/  raw_data; int /*<<< orphan*/  raw_size; } ;
struct TYPE_14__ {TYPE_6__* p_sdp_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ID_SERVICE_NAME ; 
 int /*<<< orphan*/  SDP_DISC_ATTR_LEN (int /*<<< orphan*/ ) ; 
 TYPE_8__* SDP_FindAttributeInRec (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SDP_FindProtocolListElemInRec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  SDP_TYPE_RAW ; 
 int /*<<< orphan*/  UUID_PROTOCOL_RFCOMM ; 
 TYPE_10__* p_bta_sdp_cfg ; 

__attribute__((used)) static void bta_create_raw_sdp_record(bluetooth_sdp_record *record, tSDP_DISC_REC *p_rec)
{
    tSDP_DISC_ATTR *p_attr;
    tSDP_PROTOCOL_ELEM pe;

    record->hdr.type = SDP_TYPE_RAW;
    record->hdr.service_name_length = 0;
    record->hdr.service_name = NULL;
    record->hdr.rfcomm_channel_number = -1;
    record->hdr.l2cap_psm = -1;
    record->hdr.profile_version = -1;

    /* Try to extract a service name */
    if ((p_attr = SDP_FindAttributeInRec(p_rec, ATTR_ID_SERVICE_NAME)) != NULL) {
        record->pse.hdr.service_name_length = SDP_DISC_ATTR_LEN(p_attr->attr_len_type);
        record->pse.hdr.service_name = (char *)p_attr->attr_value.v.array;
    }

    /* Try to extract an RFCOMM channel */
    if (SDP_FindProtocolListElemInRec(p_rec, UUID_PROTOCOL_RFCOMM, &pe)) {
        record->pse.hdr.rfcomm_channel_number = pe.params[0];
    }
    record->hdr.user1_ptr_len = p_bta_sdp_cfg->p_sdp_db->raw_size;
    record->hdr.user1_ptr = p_bta_sdp_cfg->p_sdp_db->raw_data;
}