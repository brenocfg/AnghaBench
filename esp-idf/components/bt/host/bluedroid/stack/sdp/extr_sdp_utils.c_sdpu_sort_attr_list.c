#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* attr_filters; } ;
typedef  TYPE_1__ tSDP_DISCOVERY_DB ;
typedef  int UINT16 ;

/* Variables and functions */
 int SDP_MAX_ATTR_FILTERS ; 

void sdpu_sort_attr_list( UINT16 num_attr, tSDP_DISCOVERY_DB *p_db )
{
    UINT16 i;
    UINT16 x;

    /* Done if no attributes to sort */
    if (num_attr <= 1) {
        return;
    } else if (num_attr > SDP_MAX_ATTR_FILTERS) {
        num_attr = SDP_MAX_ATTR_FILTERS;
    }

    num_attr--; /* for the for-loop */
    for ( i = 0; i < num_attr; ) {
        if ( p_db->attr_filters[i] > p_db->attr_filters[i + 1] ) {
            /* swap the attribute IDs and start from the beginning */
            x = p_db->attr_filters[i];
            p_db->attr_filters[i] = p_db->attr_filters[i + 1];
            p_db->attr_filters[i + 1] = x;

            i = 0;
        } else {
            i++;
        }
    }
}