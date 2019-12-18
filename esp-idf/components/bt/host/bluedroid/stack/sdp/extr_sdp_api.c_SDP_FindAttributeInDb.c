#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* p_next_rec; TYPE_2__* p_first_attr; } ;
typedef  TYPE_1__ tSDP_DISC_REC ;
struct TYPE_8__ {scalar_t__ attr_id; struct TYPE_8__* p_next_attr; } ;
typedef  TYPE_2__ tSDP_DISC_ATTR ;
struct TYPE_9__ {TYPE_1__* p_first_rec; } ;
typedef  TYPE_3__ tSDP_DISCOVERY_DB ;
typedef  scalar_t__ UINT16 ;

/* Variables and functions */

tSDP_DISC_REC *SDP_FindAttributeInDb (tSDP_DISCOVERY_DB *p_db, UINT16 attr_id,
                                      tSDP_DISC_REC *p_start_rec)
{
#if SDP_CLIENT_ENABLED == TRUE
    tSDP_DISC_REC   *p_rec;
    tSDP_DISC_ATTR  *p_attr;

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
            if (p_attr->attr_id == attr_id) {
                return (p_rec);
            }

            p_attr = p_attr->p_next_attr;
        }

        p_rec = p_rec->p_next_rec;
    }
#endif
    /* If here, no matching attribute found */
    return (NULL);
}