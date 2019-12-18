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
struct TYPE_11__ {TYPE_4__* p_first_attr; } ;
typedef  TYPE_3__ tSDP_DISC_REC ;
struct TYPE_9__ {int u16; int u32; TYPE_4__* p_sub_attr; int /*<<< orphan*/  u8; int /*<<< orphan*/  array; } ;
struct TYPE_10__ {TYPE_1__ v; } ;
struct TYPE_12__ {int attr_id; int attr_len_type; struct TYPE_12__* p_next_attr; TYPE_2__ attr_value; } ;
typedef  TYPE_4__ tSDP_DISC_ATTR ;
struct TYPE_13__ {int mem_free; scalar_t__ p_free_mem; } ;
typedef  TYPE_5__ tSDP_DISCOVERY_DB ;
typedef  int UINT8 ;
typedef  int UINT32 ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  INT32 ;

/* Variables and functions */
 int ATTR_ID_ADDITION_PROTO_DESC_LISTS ; 
 int ATTR_ID_PROTOCOL_DESC_LIST ; 
 int /*<<< orphan*/  BE_STREAM_TO_ARRAY (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BE_STREAM_TO_UINT16 (int,int*) ; 
 int /*<<< orphan*/  BE_STREAM_TO_UINT32 (int,int*) ; 
#define  BOOLEAN_DESC_TYPE 135 
#define  DATA_ELE_ALT_DESC_TYPE 134 
#define  DATA_ELE_SEQ_DESC_TYPE 133 
 int MAX_NEST_LEVELS ; 
 int /*<<< orphan*/  MAX_UUID_SIZE ; 
 int SDP_ADDITIONAL_LIST_MASK ; 
 int SDP_DISC_ATTR_LEN_MASK ; 
 int /*<<< orphan*/  SDP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  SDP_TRACE_WARNING (char*,int) ; 
#define  TEXT_STR_DESC_TYPE 132 
#define  TWO_COMP_INT_DESC_TYPE 131 
#define  UINT_DESC_TYPE 130 
#define  URL_DESC_TYPE 129 
#define  UUID_DESC_TYPE 128 
 int* sdpu_get_len_from_type (int*,int,int*) ; 
 int /*<<< orphan*/  sdpu_is_base_uuid (int*) ; 

__attribute__((used)) static UINT8 *add_attr (UINT8 *p, tSDP_DISCOVERY_DB *p_db, tSDP_DISC_REC *p_rec,
                        UINT16 attr_id, tSDP_DISC_ATTR *p_parent_attr, UINT8 nest_level)
{
    tSDP_DISC_ATTR  *p_attr;
    UINT32          attr_len;
    UINT32          total_len;
    UINT16          attr_type;
    UINT16          id;
    UINT8           type;
    UINT8           *p_end;
    UINT8           is_additional_list = nest_level & SDP_ADDITIONAL_LIST_MASK;

    nest_level &= ~(SDP_ADDITIONAL_LIST_MASK);

    type = *p++;
    p = sdpu_get_len_from_type (p, type, &attr_len);

    attr_len &= SDP_DISC_ATTR_LEN_MASK;
    attr_type = (type >> 3) & 0x0f;

    /* See if there is enough space in the database */
    if (attr_len > 4) {
        total_len = attr_len - 4 + (UINT16)sizeof (tSDP_DISC_ATTR);
    } else {
        total_len = sizeof (tSDP_DISC_ATTR);
    }

    /* Ensure it is a multiple of 4 */
    total_len = (total_len + 3) & ~3;

    /* See if there is enough space in the database */
    if (p_db->mem_free < total_len) {
        return (NULL);
    }

    p_attr                = (tSDP_DISC_ATTR *) p_db->p_free_mem;
    p_attr->attr_id       = attr_id;
    p_attr->attr_len_type = (UINT16)attr_len | (attr_type << 12);
    p_attr->p_next_attr = NULL;

    /* Store the attribute value */
    switch (attr_type) {
    case UINT_DESC_TYPE:
        if ( (is_additional_list != 0) && (attr_len == 2) ) {
            BE_STREAM_TO_UINT16 (id, p);
            if (id != ATTR_ID_PROTOCOL_DESC_LIST) {
                p -= 2;
            } else {
                /* Reserve the memory for the attribute now, as we need to add sub-attributes */
                p_db->p_free_mem += sizeof (tSDP_DISC_ATTR);
                p_db->mem_free   -= sizeof (tSDP_DISC_ATTR);
                p_end             = p + attr_len;
                total_len         = 0;

                /* SDP_TRACE_DEBUG ("SDP - attr nest level:%d(list)", nest_level); */
                if (nest_level >= MAX_NEST_LEVELS) {
                    SDP_TRACE_ERROR ("SDP - attr nesting too deep\n");
                    return (p_end);
                }

                /* Now, add the list entry */
                p = add_attr (p, p_db, p_rec, ATTR_ID_PROTOCOL_DESC_LIST, p_attr, (UINT8)(nest_level + 1));

                break;
            }
        }
    /* Case falls through */

    case TWO_COMP_INT_DESC_TYPE:
        switch (attr_len) {
        case 1:
            p_attr->attr_value.v.u8 = *p++;
            break;
        case 2:
            BE_STREAM_TO_UINT16 (p_attr->attr_value.v.u16, p);
            break;
        case 4:
            BE_STREAM_TO_UINT32 (p_attr->attr_value.v.u32, p);
            break;
        default:
            BE_STREAM_TO_ARRAY (p, p_attr->attr_value.v.array, (INT32)attr_len);
            break;
        }
        break;

    case UUID_DESC_TYPE:
        switch (attr_len) {
        case 2:
            BE_STREAM_TO_UINT16 (p_attr->attr_value.v.u16, p);
            break;
        case 4:
            BE_STREAM_TO_UINT32 (p_attr->attr_value.v.u32, p);
            if (p_attr->attr_value.v.u32 < 0x10000) {
                attr_len = 2;
                p_attr->attr_len_type = (UINT16)attr_len | (attr_type << 12);
                p_attr->attr_value.v.u16 = (UINT16) p_attr->attr_value.v.u32;

            }
            break;
        case 16:
            /* See if we can compress his UUID down to 16 or 32bit UUIDs */
            if (sdpu_is_base_uuid (p)) {
                if ((p[0] == 0) && (p[1] == 0)) {
                    p_attr->attr_len_type = (p_attr->attr_len_type & ~SDP_DISC_ATTR_LEN_MASK) | 2;
                    p += 2;
                    BE_STREAM_TO_UINT16 (p_attr->attr_value.v.u16, p);
                    p += MAX_UUID_SIZE - 4;
                } else {
                    p_attr->attr_len_type = (p_attr->attr_len_type & ~SDP_DISC_ATTR_LEN_MASK) | 4;
                    BE_STREAM_TO_UINT32 (p_attr->attr_value.v.u32, p);
                    p += MAX_UUID_SIZE - 4;
                }
            } else {
                /* coverity[overrun-local] */
                /*
                   Event overrun-local: Overrun of static array "p_attr->attr_value.v.array" of size 4 at position 15 with index variable "ijk"
                   False-positive: SDP uses scratch buffer to hold the attribute value.
                   The actual size of tSDP_DISC_ATVAL does not matter.
                   If the array size in tSDP_DISC_ATVAL is increase, we would increase the system RAM usage unnecessarily
                */
                BE_STREAM_TO_ARRAY (p, p_attr->attr_value.v.array, (INT32)attr_len);
            }
            break;
        default:
            SDP_TRACE_WARNING ("SDP - bad len in UUID attr: %d\n", attr_len);
            return (p + attr_len);
        }
        break;

    case DATA_ELE_SEQ_DESC_TYPE:
    case DATA_ELE_ALT_DESC_TYPE:
        /* Reserve the memory for the attribute now, as we need to add sub-attributes */
        p_db->p_free_mem += sizeof (tSDP_DISC_ATTR);
        p_db->mem_free   -= sizeof (tSDP_DISC_ATTR);
        p_end             = p + attr_len;
        total_len         = 0;

        /* SDP_TRACE_DEBUG ("SDP - attr nest level:%d", nest_level); */
        if (nest_level >= MAX_NEST_LEVELS) {
            SDP_TRACE_ERROR ("SDP - attr nesting too deep\n");
            return (p_end);
        }
        if (is_additional_list != 0 || attr_id == ATTR_ID_ADDITION_PROTO_DESC_LISTS) {
            nest_level |= SDP_ADDITIONAL_LIST_MASK;
        }
        /* SDP_TRACE_DEBUG ("SDP - attr nest level:0x%x(finish)", nest_level); */

        while (p < p_end) {
            /* Now, add the list entry */
            p = add_attr (p, p_db, p_rec, 0, p_attr, (UINT8)(nest_level + 1));

            if (!p) {
                return (NULL);
            }
        }
        break;

    case TEXT_STR_DESC_TYPE:
    case URL_DESC_TYPE:
        BE_STREAM_TO_ARRAY (p, p_attr->attr_value.v.array, (INT32)attr_len);
        break;

    case BOOLEAN_DESC_TYPE:
        switch (attr_len) {
        case 1:
            p_attr->attr_value.v.u8 = *p++;
            break;
        default:
            SDP_TRACE_WARNING ("SDP - bad len in boolean attr: %d\n", attr_len);
            return (p + attr_len);
        }
        break;

    default:    /* switch (attr_type) */
        break;
    }

    p_db->p_free_mem += total_len;
    p_db->mem_free   -= total_len;

    /* Add the attribute to the end of the chain */
    if (!p_parent_attr) {
        if (!p_rec->p_first_attr) {
            p_rec->p_first_attr = p_attr;
        } else {
            tSDP_DISC_ATTR  *p_attr1 = p_rec->p_first_attr;

            while (p_attr1->p_next_attr) {
                p_attr1 = p_attr1->p_next_attr;
            }

            p_attr1->p_next_attr = p_attr;
        }
    } else {
        if (!p_parent_attr->attr_value.v.p_sub_attr) {
            p_parent_attr->attr_value.v.p_sub_attr = p_attr;
            /* SDP_TRACE_DEBUG ("parent:0x%x(id:%d), ch:0x%x(id:%d)",
                p_parent_attr, p_parent_attr->attr_id, p_attr, p_attr->attr_id); */
        } else {
            tSDP_DISC_ATTR  *p_attr1 = p_parent_attr->attr_value.v.p_sub_attr;
            /* SDP_TRACE_DEBUG ("parent:0x%x(id:%d), ch1:0x%x(id:%d)",
                p_parent_attr, p_parent_attr->attr_id, p_attr1, p_attr1->attr_id); */

            while (p_attr1->p_next_attr) {
                p_attr1 = p_attr1->p_next_attr;
            }

            p_attr1->p_next_attr = p_attr;
            /* SDP_TRACE_DEBUG ("new ch:0x%x(id:%d)", p_attr, p_attr->attr_id); */
        }
    }

    return (p);
}