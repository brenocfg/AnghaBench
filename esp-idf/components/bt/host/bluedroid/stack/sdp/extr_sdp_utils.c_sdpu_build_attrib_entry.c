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
struct TYPE_3__ {int id; int type; int len; int /*<<< orphan*/ * value_ptr; } ;
typedef  TYPE_1__ tSDP_ATTRIBUTE ;
typedef  int /*<<< orphan*/  UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_BE_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
#define  DATA_ELE_ALT_DESC_TYPE 131 
#define  DATA_ELE_SEQ_DESC_TYPE 130 
 int SIZE_EIGHT_BYTES ; 
 int SIZE_FOUR_BYTES ; 
 int SIZE_IN_NEXT_BYTE ; 
 int SIZE_IN_NEXT_LONG ; 
 int SIZE_IN_NEXT_WORD ; 
 int SIZE_ONE_BYTE ; 
 int SIZE_SIXTEEN_BYTES ; 
 int SIZE_TWO_BYTES ; 
#define  TEXT_STR_DESC_TYPE 129 
 int /*<<< orphan*/  UINT16_TO_BE_STREAM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UINT32_TO_BE_STREAM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UINT8_TO_BE_STREAM (int /*<<< orphan*/ *,int) ; 
 int UINT_DESC_TYPE ; 
#define  URL_DESC_TYPE 128 

UINT8 *sdpu_build_attrib_entry (UINT8 *p_out, tSDP_ATTRIBUTE *p_attr)
{
    /* First, store the attribute ID. Goes as a UINT */
    UINT8_TO_BE_STREAM  (p_out, (UINT_DESC_TYPE << 3) | SIZE_TWO_BYTES);
    UINT16_TO_BE_STREAM (p_out, p_attr->id);

    /* the attribute is in the db record.
     * assuming the attribute len is less than SDP_MAX_ATTR_LEN */
    switch (p_attr->type) {
    case TEXT_STR_DESC_TYPE:    /* 4 */
    case DATA_ELE_SEQ_DESC_TYPE:/* 6 */
    case DATA_ELE_ALT_DESC_TYPE:/* 7 */
    case URL_DESC_TYPE:         /* 8 */
#if (SDP_MAX_ATTR_LEN > 0xFFFF)
        if (p_attr->len > 0xFFFF) {
            UINT8_TO_BE_STREAM (p_out, (p_attr->type << 3) | SIZE_IN_NEXT_LONG);
            UINT32_TO_BE_STREAM (p_out, p_attr->len);
        } else

#endif /* 0xFFFF - 0xFF */
        {
#if (SDP_MAX_ATTR_LEN > 0xFF)
            if (p_attr->len > 0xFF) {
                UINT8_TO_BE_STREAM (p_out, (p_attr->type << 3) | SIZE_IN_NEXT_WORD);
                UINT16_TO_BE_STREAM (p_out, p_attr->len);
            } else

#endif /* 0xFF and less*/
            {
                UINT8_TO_BE_STREAM (p_out, (p_attr->type << 3) | SIZE_IN_NEXT_BYTE);
                UINT8_TO_BE_STREAM (p_out, p_attr->len);
            }
        }
        if (p_attr->value_ptr != NULL) {
            ARRAY_TO_BE_STREAM (p_out, p_attr->value_ptr, (int)p_attr->len);
        }

        return (p_out);
    }

    /* Now, store the attribute value */
    switch (p_attr->len) {
    case 1:
        UINT8_TO_BE_STREAM (p_out, (p_attr->type << 3) | SIZE_ONE_BYTE);
        break;
    case 2:
        UINT8_TO_BE_STREAM  (p_out, (p_attr->type << 3) | SIZE_TWO_BYTES);
        break;
    case 4:
        UINT8_TO_BE_STREAM  (p_out, (p_attr->type << 3) | SIZE_FOUR_BYTES);
        break;
    case 8:
        UINT8_TO_BE_STREAM  (p_out, (p_attr->type << 3) | SIZE_EIGHT_BYTES);
        break;
    case 16:
        UINT8_TO_BE_STREAM  (p_out, (p_attr->type << 3) | SIZE_SIXTEEN_BYTES);
        break;
    default:
        UINT8_TO_BE_STREAM (p_out, (p_attr->type << 3) | SIZE_IN_NEXT_BYTE);
        UINT8_TO_BE_STREAM (p_out, p_attr->len);
        break;
    }

    if (p_attr->value_ptr != NULL) {
        ARRAY_TO_BE_STREAM (p_out, p_attr->value_ptr, (int)p_attr->len);
    }

    return (p_out);
}