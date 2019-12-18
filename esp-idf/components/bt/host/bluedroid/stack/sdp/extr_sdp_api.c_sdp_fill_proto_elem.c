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
struct TYPE_9__ {scalar_t__ num_params; scalar_t__* params; scalar_t__ protocol_uuid; } ;
typedef  TYPE_3__ tSDP_PROTOCOL_ELEM ;
struct TYPE_7__ {scalar_t__ u16; scalar_t__ u8; TYPE_4__* p_sub_attr; } ;
struct TYPE_8__ {TYPE_1__ v; } ;
struct TYPE_10__ {TYPE_2__ attr_value; int /*<<< orphan*/  attr_len_type; struct TYPE_10__* p_next_attr; } ;
typedef  TYPE_4__ tSDP_DISC_ATTR ;
typedef  scalar_t__ UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ DATA_ELE_SEQ_DESC_TYPE ; 
 int /*<<< orphan*/  FALSE ; 
 int SDP_DISC_ATTR_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ SDP_DISC_ATTR_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ SDP_MAX_PROTOCOL_PARAMS ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UINT_DESC_TYPE ; 
 scalar_t__ UUID_DESC_TYPE ; 

__attribute__((used)) static BOOLEAN sdp_fill_proto_elem( tSDP_DISC_ATTR  *p_attr, UINT16 layer_uuid,
                                    tSDP_PROTOCOL_ELEM *p_elem)
{
    tSDP_DISC_ATTR  *p_sattr;

    /* Walk through the protocol descriptor list */
    for (p_attr = p_attr->attr_value.v.p_sub_attr; p_attr; p_attr = p_attr->p_next_attr) {
        /* Safety check - each entry should itself be a sequence */
        if (SDP_DISC_ATTR_TYPE(p_attr->attr_len_type) != DATA_ELE_SEQ_DESC_TYPE) {
            return (FALSE);
        }

        /* Now, see if the entry contains the layer we are interested in */
        for (p_sattr = p_attr->attr_value.v.p_sub_attr; p_sattr; p_sattr = p_sattr->p_next_attr) {
            /* SDP_TRACE_DEBUG ("SDP - p_sattr 0x%x, layer_uuid:0x%x, u16:0x%x####",
                p_sattr, layer_uuid, p_sattr->attr_value.v.u16); */

            if ((SDP_DISC_ATTR_TYPE(p_sattr->attr_len_type) == UUID_DESC_TYPE)
                    && (SDP_DISC_ATTR_LEN(p_sattr->attr_len_type) == 2)
                    && (p_sattr->attr_value.v.u16 == layer_uuid)) {
                /* Bingo. Now fill in the passed element */
                p_elem->protocol_uuid = layer_uuid;
                p_elem->num_params = 0;

                /* Store the parameters, if any */
                for (p_sattr = p_sattr->p_next_attr; p_sattr; p_sattr = p_sattr->p_next_attr) {
                    if (SDP_DISC_ATTR_TYPE(p_sattr->attr_len_type) != UINT_DESC_TYPE) {
                        break;
                    }

                    if (SDP_DISC_ATTR_LEN(p_sattr->attr_len_type) == 2) {
                        p_elem->params[p_elem->num_params++] = p_sattr->attr_value.v.u16;
                    } else {
                        p_elem->params[p_elem->num_params++] = p_sattr->attr_value.v.u8;
                    }

                    if (p_elem->num_params >= SDP_MAX_PROTOCOL_PARAMS) {
                        break;
                    }
                }
                return (TRUE);
            }
        }
    }

    return (FALSE);
}