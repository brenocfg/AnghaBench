#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* p_first_attr; } ;
typedef  TYPE_3__ tSDP_DISC_REC ;
struct TYPE_6__ {scalar_t__ u16; TYPE_4__* p_sub_attr; } ;
struct TYPE_7__ {TYPE_1__ v; } ;
struct TYPE_9__ {scalar_t__ attr_id; struct TYPE_9__* p_next_attr; TYPE_2__ attr_value; int /*<<< orphan*/  attr_len_type; } ;
typedef  TYPE_4__ tSDP_DISC_ATTR ;
typedef  scalar_t__ UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ ATTR_ID_BT_PROFILE_DESC_LIST ; 
 scalar_t__ DATA_ELE_SEQ_DESC_TYPE ; 
 int /*<<< orphan*/  FALSE ; 
 int SDP_DISC_ATTR_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ SDP_DISC_ATTR_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UINT_DESC_TYPE ; 
 scalar_t__ UUID_DESC_TYPE ; 

BOOLEAN SDP_FindProfileVersionInRec (tSDP_DISC_REC *p_rec, UINT16 profile_uuid, UINT16 *p_version)
{
#if SDP_CLIENT_ENABLED == TRUE
    tSDP_DISC_ATTR  *p_attr, *p_sattr;

    p_attr = p_rec->p_first_attr;
    while (p_attr) {
        /* Find the profile descriptor list */
        if ((p_attr->attr_id == ATTR_ID_BT_PROFILE_DESC_LIST)
                && (SDP_DISC_ATTR_TYPE(p_attr->attr_len_type) == DATA_ELE_SEQ_DESC_TYPE)) {
            /* Walk through the protocol descriptor list */
            for (p_attr = p_attr->attr_value.v.p_sub_attr; p_attr; p_attr = p_attr->p_next_attr) {
                /* Safety check - each entry should itself be a sequence */
                if (SDP_DISC_ATTR_TYPE(p_attr->attr_len_type) != DATA_ELE_SEQ_DESC_TYPE) {
                    return (FALSE);
                }

                /* Now, see if the entry contains the profile UUID we are interested in */
                for (p_sattr = p_attr->attr_value.v.p_sub_attr; p_sattr; p_sattr = p_sattr->p_next_attr) {
                    if ((SDP_DISC_ATTR_TYPE(p_sattr->attr_len_type) == UUID_DESC_TYPE)
                            && (SDP_DISC_ATTR_LEN(p_sattr->attr_len_type) == 2)  /* <- This is bytes, not size code! */
                            && (p_sattr->attr_value.v.u16 == profile_uuid)) {
                        /* Now fill in the major and minor numbers */
                        /* if the attribute matches the description for version (type UINT, size 2 bytes) */
                        p_sattr = p_sattr->p_next_attr;

                        if ((SDP_DISC_ATTR_TYPE(p_sattr->attr_len_type) == UINT_DESC_TYPE) &&
                                (SDP_DISC_ATTR_LEN(p_sattr->attr_len_type) == 2)) {
                            /* The high order 8 bits is the major number, low order is the minor number (big endian) */
                            *p_version = p_sattr->attr_value.v.u16;

                            return (TRUE);
                        } else {
                            return (FALSE);    /* The type and/or size was not valid for the profile list version */
                        }
                    }
                }
            }

            return (FALSE);
        }
        p_attr = p_attr->p_next_attr;
    }
#endif  /* CLIENT_ENABLED == TRUE */

    /* If here, no match found */
    return (FALSE);
}