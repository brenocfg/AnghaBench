#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_12__ {TYPE_5__* p_first_attr; } ;
typedef  TYPE_4__ tSDP_DISC_REC ;
struct TYPE_10__ {int /*<<< orphan*/ * array; TYPE_5__* p_sub_attr; } ;
struct TYPE_11__ {TYPE_2__ v; } ;
struct TYPE_13__ {scalar_t__ attr_id; struct TYPE_13__* p_next_attr; TYPE_3__ attr_value; int /*<<< orphan*/  attr_len_type; } ;
typedef  TYPE_5__ tSDP_DISC_ATTR ;
struct TYPE_9__ {int /*<<< orphan*/ * uuid128; } ;
struct TYPE_14__ {size_t len; TYPE_1__ uu; } ;
typedef  TYPE_6__ tBT_UUID ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ ATTR_ID_SERVICE_CLASS_ID_LIST ; 
 scalar_t__ ATTR_ID_SERVICE_ID ; 
 scalar_t__ DATA_ELE_SEQ_DESC_TYPE ; 
 int /*<<< orphan*/  FALSE ; 
 size_t LEN_UUID_128 ; 
 int SDP_DISC_ATTR_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ SDP_DISC_ATTR_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UUID_DESC_TYPE ; 

BOOLEAN SDP_FindServiceUUIDInRec_128bit(tSDP_DISC_REC *p_rec, tBT_UUID *p_uuid)
{
#if SDP_CLIENT_ENABLED == TRUE
    tSDP_DISC_ATTR  *p_attr, *p_sattr;

    p_attr = p_rec->p_first_attr;

    while (p_attr) {
        if ((p_attr->attr_id == ATTR_ID_SERVICE_CLASS_ID_LIST)
                && (SDP_DISC_ATTR_TYPE(p_attr->attr_len_type) == DATA_ELE_SEQ_DESC_TYPE)) {
            for (p_sattr = p_attr->attr_value.v.p_sub_attr; p_sattr; p_sattr = p_sattr->p_next_attr) {
                if (SDP_DISC_ATTR_TYPE(p_sattr->attr_len_type) == UUID_DESC_TYPE) {
                    /* only support 128 bits UUID for now */
                    if (SDP_DISC_ATTR_LEN(p_sattr->attr_len_type) == 16) {
                        p_uuid->len = LEN_UUID_128;
                        for (uint8_t i = 0; i != LEN_UUID_128; ++i) {
                            p_uuid->uu.uuid128[i] = p_sattr->attr_value.v.array[LEN_UUID_128 - i - 1];
                        }
                    }
                    return (TRUE);
                }
            }
            break;
        } else if (p_attr->attr_id == ATTR_ID_SERVICE_ID) {
            if ((SDP_DISC_ATTR_TYPE(p_attr->attr_len_type) == UUID_DESC_TYPE)
                    /* only support 128 bits UUID for now */
                    && (SDP_DISC_ATTR_LEN(p_attr->attr_len_type) == 16)) {
                p_uuid->len = LEN_UUID_128;
                for (uint8_t i = 0; i != LEN_UUID_128; ++i) {
                    p_uuid->uu.uuid128[i] = p_attr->attr_value.v.array[LEN_UUID_128 - i - 1];
                }
                return (TRUE);
            }
        }
        p_attr = p_attr->p_next_attr;
    }
    return FALSE;
#else
    return FALSE;
#endif
}