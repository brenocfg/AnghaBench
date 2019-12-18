#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSDP_UUID ;
struct TYPE_5__ {int mem_size; int mem_free; scalar_t__ num_attr_filters; int /*<<< orphan*/ * attr_filters; scalar_t__ num_uuid_filters; int /*<<< orphan*/ * uuid_filters; int /*<<< orphan*/ * p_free_mem; int /*<<< orphan*/ * p_first_rec; } ;
typedef  TYPE_1__ tSDP_DISCOVERY_DB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
typedef  scalar_t__ UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SDP_MAX_ATTR_FILTERS ; 
 scalar_t__ SDP_MAX_UUID_FILTERS ; 
 int /*<<< orphan*/  SDP_TRACE_ERROR (char*,int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sdpu_sort_attr_list (scalar_t__,TYPE_1__*) ; 

BOOLEAN SDP_InitDiscoveryDb (tSDP_DISCOVERY_DB *p_db, UINT32 len, UINT16 num_uuid,
                             tSDP_UUID *p_uuid_list, UINT16 num_attr, UINT16 *p_attr_list)
{
#if SDP_CLIENT_ENABLED == TRUE
    UINT16  xx;

    /* verify the parameters */
    if (p_db == NULL || (sizeof (tSDP_DISCOVERY_DB) > len) ||
            num_attr > SDP_MAX_ATTR_FILTERS || num_uuid > SDP_MAX_UUID_FILTERS) {
        SDP_TRACE_ERROR("SDP_InitDiscoveryDb Illegal param: p_db 0x%x, len %d, num_uuid %d, num_attr %d",
                        (UINT32)p_db, len, num_uuid, num_attr);

        return (FALSE);
    }

    memset (p_db, 0, (size_t)len);

    p_db->mem_size = len - sizeof (tSDP_DISCOVERY_DB);
    p_db->mem_free = p_db->mem_size;
    p_db->p_first_rec = NULL;
    p_db->p_free_mem = (UINT8 *)(p_db + 1);

    for (xx = 0; xx < num_uuid; xx++) {
        p_db->uuid_filters[xx] = *p_uuid_list++;
    }

    p_db->num_uuid_filters = num_uuid;

    for (xx = 0; xx < num_attr; xx++) {
        p_db->attr_filters[xx] = *p_attr_list++;
    }

    /* sort attributes */
    sdpu_sort_attr_list( num_attr, p_db );

    p_db->num_attr_filters = num_attr;
#endif
    return (TRUE);
}