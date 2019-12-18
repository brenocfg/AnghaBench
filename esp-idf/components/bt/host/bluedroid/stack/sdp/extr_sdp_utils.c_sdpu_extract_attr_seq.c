#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t num_attr; TYPE_1__* attr_entry; } ;
typedef  TYPE_2__ tSDP_ATTR_SEQ ;
typedef  int UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_4__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_STREAM_TO_UINT16 (scalar_t__,int*) ; 
 int /*<<< orphan*/  BE_STREAM_TO_UINT32 (scalar_t__,int*) ; 
 int /*<<< orphan*/  BE_STREAM_TO_UINT8 (scalar_t__,int*) ; 
 int DATA_ELE_SEQ_DESC_TYPE ; 
 size_t MAX_ATTR_PER_SEQ ; 
#define  SIZE_FOUR_BYTES 132 
#define  SIZE_IN_NEXT_BYTE 131 
#define  SIZE_IN_NEXT_LONG 130 
#define  SIZE_IN_NEXT_WORD 129 
#define  SIZE_TWO_BYTES 128 
 int UINT_DESC_TYPE ; 

UINT8 *sdpu_extract_attr_seq (UINT8 *p, UINT16 param_len, tSDP_ATTR_SEQ *p_seq)
{
    UINT8   *p_end_list;
    UINT8   descr, type, size;
    UINT32  list_len, attr_len;

    /* Assume none found */
    p_seq->num_attr = 0;

    /* Get attribute sequence info */
    BE_STREAM_TO_UINT8 (descr, p);
    type = descr >> 3;
    size = descr & 7;

    if (type != DATA_ELE_SEQ_DESC_TYPE) {
        return (p);
    }

    switch (size) {
    case SIZE_IN_NEXT_BYTE:
        BE_STREAM_TO_UINT8 (list_len, p);
        break;

    case SIZE_IN_NEXT_WORD:
        BE_STREAM_TO_UINT16 (list_len, p);
        break;

    case SIZE_IN_NEXT_LONG:
        BE_STREAM_TO_UINT32 (list_len, p);
        break;

    default:
        return (p);
    }

    if (list_len > param_len) {
        return (p);
    }

    p_end_list = p + list_len;

    /* Loop through, extracting the attribute IDs */
    for ( ; p < p_end_list ; ) {
        BE_STREAM_TO_UINT8 (descr, p);
        type = descr >> 3;
        size = descr & 7;

        if (type != UINT_DESC_TYPE) {
            return (p);
        }

        switch (size) {
        case SIZE_TWO_BYTES:
            attr_len = 2;
            break;
        case SIZE_FOUR_BYTES:
            attr_len = 4;
            break;
        case SIZE_IN_NEXT_BYTE:
            BE_STREAM_TO_UINT8 (attr_len, p);
            break;
        case SIZE_IN_NEXT_WORD:
            BE_STREAM_TO_UINT16 (attr_len, p);
            break;
        case SIZE_IN_NEXT_LONG:
            BE_STREAM_TO_UINT32 (attr_len, p);
            break;
        default:
            return (NULL);
            break;
        }

        /* Attribute length must be 2-bytes or 4-bytes for a paired entry. */
        if (attr_len == 2) {
            BE_STREAM_TO_UINT16 (p_seq->attr_entry[p_seq->num_attr].start, p);
            p_seq->attr_entry[p_seq->num_attr].end = p_seq->attr_entry[p_seq->num_attr].start;
        } else if (attr_len == 4) {
            BE_STREAM_TO_UINT16 (p_seq->attr_entry[p_seq->num_attr].start, p);
            BE_STREAM_TO_UINT16 (p_seq->attr_entry[p_seq->num_attr].end, p);
        } else {
            return (NULL);
        }

        /* We can only do so many */
        if (++p_seq->num_attr >= MAX_ATTR_PER_SEQ) {
            return (NULL);
        }
    }

    return (p);
}