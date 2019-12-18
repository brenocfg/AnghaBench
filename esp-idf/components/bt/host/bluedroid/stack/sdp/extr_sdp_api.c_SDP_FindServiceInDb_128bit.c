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
struct TYPE_11__ {struct TYPE_11__* p_next_rec; TYPE_4__* p_first_attr; } ;
typedef  TYPE_3__ tSDP_DISC_REC ;
struct TYPE_9__ {TYPE_4__* p_sub_attr; } ;
struct TYPE_10__ {TYPE_1__ v; } ;
struct TYPE_12__ {scalar_t__ attr_id; struct TYPE_12__* p_next_attr; int /*<<< orphan*/  attr_len_type; TYPE_2__ attr_value; } ;
typedef  TYPE_4__ tSDP_DISC_ATTR ;
struct TYPE_13__ {TYPE_3__* p_first_rec; } ;
typedef  TYPE_5__ tSDP_DISCOVERY_DB ;

/* Variables and functions */
 scalar_t__ ATTR_ID_SERVICE_CLASS_ID_LIST ; 
 scalar_t__ ATTR_ID_SERVICE_ID ; 
 scalar_t__ DATA_ELE_SEQ_DESC_TYPE ; 
 int SDP_DISC_ATTR_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__ SDP_DISC_ATTR_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ UUID_DESC_TYPE ; 

tSDP_DISC_REC *SDP_FindServiceInDb_128bit(tSDP_DISCOVERY_DB *p_db, tSDP_DISC_REC *p_start_rec)
{
#if SDP_CLIENT_ENABLED == TRUE
    tSDP_DISC_REC   *p_rec;
    tSDP_DISC_ATTR  *p_attr, *p_sattr;

    /* Must have a valid database */
    if (p_db == NULL) {
        return (NULL);
    }

    if (!p_start_rec) {
        p_rec = p_db->p_first_rec;
    } else {
        p_rec = p_start_rec->p_next_rec;
    }

    while (p_rec) {
        p_attr = p_rec->p_first_attr;
        while (p_attr) {
            if ((p_attr->attr_id == ATTR_ID_SERVICE_CLASS_ID_LIST)
                    && (SDP_DISC_ATTR_TYPE(p_attr->attr_len_type) == DATA_ELE_SEQ_DESC_TYPE)) {
                for (p_sattr = p_attr->attr_value.v.p_sub_attr; p_sattr; p_sattr = p_sattr->p_next_attr) {
                    if ((SDP_DISC_ATTR_TYPE(p_sattr->attr_len_type) == UUID_DESC_TYPE)
                            && (SDP_DISC_ATTR_LEN(p_sattr->attr_len_type) == 16)) {
                        return (p_rec);
                    }
                }
                break;
            } else if (p_attr->attr_id == ATTR_ID_SERVICE_ID) {
                if ((SDP_DISC_ATTR_TYPE(p_attr->attr_len_type) == UUID_DESC_TYPE)
                        && (SDP_DISC_ATTR_LEN(p_attr->attr_len_type) == 16)) {
                    return (p_rec);
                }
            }

            p_attr = p_attr->p_next_attr;
        }

        p_rec = p_rec->p_next_rec;
    }
#endif
    /* If here, no matching UUID found */
    return (NULL);
}