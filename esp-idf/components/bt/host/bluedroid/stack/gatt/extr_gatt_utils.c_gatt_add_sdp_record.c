#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int num_params; void** params; int /*<<< orphan*/  protocol_uuid; } ;
typedef  TYPE_2__ tSDP_PROTOCOL_ELEM ;
struct TYPE_6__ {int /*<<< orphan*/  uuid128; int /*<<< orphan*/  uuid32; int /*<<< orphan*/  uuid16; } ;
struct TYPE_8__ {int len; TYPE_1__ uu; } ;
typedef  TYPE_3__ tBT_UUID ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  void* UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_BE_STREAM_REVERSE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  ATTR_ID_BROWSE_GROUP_LIST ; 
 int /*<<< orphan*/  ATTR_ID_SERVICE_CLASS_ID_LIST ; 
 void* BT_PSM_ATT ; 
 int /*<<< orphan*/  DATA_ELE_SEQ_DESC_TYPE ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,void*,void*) ; 
 int /*<<< orphan*/  GATT_TRACE_ERROR (char*,int) ; 
#define  LEN_UUID_128 130 
#define  LEN_UUID_16 129 
#define  LEN_UUID_32 128 
 int /*<<< orphan*/  SDP_AddAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDP_AddProtocolList (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  SDP_AddServiceClassIdList (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDP_AddUuidSequence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void**) ; 
 int /*<<< orphan*/  SDP_CreateRecord () ; 
 int /*<<< orphan*/  SDP_DeleteRecord (int /*<<< orphan*/ ) ; 
 int SIZE_FOUR_BYTES ; 
 int SIZE_SIXTEEN_BYTES ; 
 int /*<<< orphan*/  UINT32_TO_BE_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_BE_STREAM (int /*<<< orphan*/ *,int) ; 
 int UUID_DESC_TYPE ; 
 int /*<<< orphan*/  UUID_PROTOCOL_ATT ; 
 int /*<<< orphan*/  UUID_PROTOCOL_L2CAP ; 
 void* UUID_SERVCLASS_PUBLIC_BROWSE_GROUP ; 

UINT32 gatt_add_sdp_record (tBT_UUID *p_uuid, UINT16 start_hdl, UINT16 end_hdl)
{
    tSDP_PROTOCOL_ELEM  proto_elem_list[2];
    UINT32              sdp_handle;
    UINT16              list = UUID_SERVCLASS_PUBLIC_BROWSE_GROUP;
    UINT8               buff[60];
    UINT8               *p = buff;

    GATT_TRACE_DEBUG("gatt_add_sdp_record s_hdl=0x%x  s_hdl=0x%x", start_hdl, end_hdl);

    if ((sdp_handle = SDP_CreateRecord()) == 0) {
        return 0;
    }

    switch (p_uuid->len) {
    case LEN_UUID_16:
        SDP_AddServiceClassIdList(sdp_handle, 1, &p_uuid->uu.uuid16);
        break;

    case LEN_UUID_32:
        UINT8_TO_BE_STREAM (p, (UUID_DESC_TYPE << 3) | SIZE_FOUR_BYTES);
        UINT32_TO_BE_STREAM (p, p_uuid->uu.uuid32);
        SDP_AddAttribute (sdp_handle, ATTR_ID_SERVICE_CLASS_ID_LIST, DATA_ELE_SEQ_DESC_TYPE,
                          (UINT32) (p - buff), buff);
        break;

    case LEN_UUID_128:
        UINT8_TO_BE_STREAM (p, (UUID_DESC_TYPE << 3) | SIZE_SIXTEEN_BYTES);
        ARRAY_TO_BE_STREAM_REVERSE (p, p_uuid->uu.uuid128, LEN_UUID_128);
        SDP_AddAttribute (sdp_handle, ATTR_ID_SERVICE_CLASS_ID_LIST, DATA_ELE_SEQ_DESC_TYPE,
                          (UINT32) (p - buff), buff);
        break;

    default:
        GATT_TRACE_ERROR("inavlid UUID len=%d", p_uuid->len);
        SDP_DeleteRecord(sdp_handle);
        return 0;
        break;
    }

    /*** Fill out the protocol element sequence for SDP ***/
    proto_elem_list[0].protocol_uuid = UUID_PROTOCOL_L2CAP;
    proto_elem_list[0].num_params    = 1;
    proto_elem_list[0].params[0]     = BT_PSM_ATT;
    proto_elem_list[1].protocol_uuid = UUID_PROTOCOL_ATT;
    proto_elem_list[1].num_params    = 2;
    proto_elem_list[1].params[0]     = start_hdl;
    proto_elem_list[1].params[1]     = end_hdl;

    SDP_AddProtocolList(sdp_handle, 2, proto_elem_list);

    /* Make the service browseable */
    SDP_AddUuidSequence (sdp_handle, ATTR_ID_BROWSE_GROUP_LIST, 1, &list);

    return (sdp_handle);
}