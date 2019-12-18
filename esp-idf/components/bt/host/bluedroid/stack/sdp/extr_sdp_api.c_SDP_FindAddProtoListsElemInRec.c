#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSDP_PROTOCOL_ELEM ;
struct TYPE_9__ {TYPE_4__* p_first_attr; } ;
typedef  TYPE_3__ tSDP_DISC_REC ;
struct TYPE_7__ {TYPE_4__* p_sub_attr; } ;
struct TYPE_8__ {TYPE_1__ v; } ;
struct TYPE_10__ {scalar_t__ attr_id; struct TYPE_10__* p_next_attr; int /*<<< orphan*/  attr_len_type; TYPE_2__ attr_value; } ;
typedef  TYPE_4__ tSDP_DISC_ATTR ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ ATTR_ID_ADDITION_PROTO_DESC_LISTS ; 
 scalar_t__ DATA_ELE_SEQ_DESC_TYPE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SDP_DISC_ATTR_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sdp_fill_proto_elem (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

BOOLEAN SDP_FindAddProtoListsElemInRec (tSDP_DISC_REC *p_rec, UINT16 layer_uuid, tSDP_PROTOCOL_ELEM *p_elem)
{
#if SDP_CLIENT_ENABLED == TRUE
    tSDP_DISC_ATTR  *p_attr, *p_sattr;
    BOOLEAN         ret = FALSE;

    p_attr = p_rec->p_first_attr;
    while (p_attr) {
        /* Find the additional protocol descriptor list attribute */
        if ((p_attr->attr_id == ATTR_ID_ADDITION_PROTO_DESC_LISTS)
                && (SDP_DISC_ATTR_TYPE(p_attr->attr_len_type) == DATA_ELE_SEQ_DESC_TYPE)) {
            for (p_sattr = p_attr->attr_value.v.p_sub_attr; p_sattr; p_sattr = p_sattr->p_next_attr) {
                /* Safety check - each entry should itself be a sequence */
                if (SDP_DISC_ATTR_TYPE(p_sattr->attr_len_type) == DATA_ELE_SEQ_DESC_TYPE) {
                    if ( (ret = sdp_fill_proto_elem(p_sattr, layer_uuid, p_elem)) == TRUE) {
                        break;
                    }
                }
            }
            return ret;
        }
        p_attr = p_attr->p_next_attr;
    }
#endif
    /* If here, no match found */
    return (FALSE);
}