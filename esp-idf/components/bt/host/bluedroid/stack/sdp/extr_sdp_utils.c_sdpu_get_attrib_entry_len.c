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
struct TYPE_3__ {int type; int len; } ;
typedef  TYPE_1__ tSDP_ATTRIBUTE ;
typedef  int UINT16 ;

/* Variables and functions */
#define  DATA_ELE_ALT_DESC_TYPE 131 
#define  DATA_ELE_SEQ_DESC_TYPE 130 
#define  TEXT_STR_DESC_TYPE 129 
#define  URL_DESC_TYPE 128 

UINT16 sdpu_get_attrib_entry_len(tSDP_ATTRIBUTE *p_attr)
{
    UINT16 len = 3;

    /* the attribute is in the db record.
     * assuming the attribute len is less than SDP_MAX_ATTR_LEN */
    switch (p_attr->type) {
    case TEXT_STR_DESC_TYPE:    /* 4 */
    case DATA_ELE_SEQ_DESC_TYPE:/* 6 */
    case DATA_ELE_ALT_DESC_TYPE:/* 7 */
    case URL_DESC_TYPE:         /* 8 */
#if (SDP_MAX_ATTR_LEN > 0xFFFF)
        if (p_attr->len > 0xFFFF) {
            len += 5;
        } else

#endif/* 0xFFFF - 0xFF */
        {
#if (SDP_MAX_ATTR_LEN > 0xFF)
            if (p_attr->len > 0xFF) {
                len += 3;
            } else

#endif /* 0xFF and less*/
            {
                len += 2;
            }
        }
        len += p_attr->len;
        return len;
    }

    /* Now, the attribute value */
    switch (p_attr->len) {
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
        len += 1;
        break;
    default:
        len += 2;
        break;
    }

    len += p_attr->len;
    return len;
}