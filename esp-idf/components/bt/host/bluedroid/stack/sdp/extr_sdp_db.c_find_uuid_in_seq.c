#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UINT8 ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int DATA_ELE_SEQ_DESC_TYPE ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int UUID_DESC_TYPE ; 
 scalar_t__ sdpu_compare_uuid_arrays (int*,int,int*,int /*<<< orphan*/ ) ; 
 int* sdpu_get_len_from_type (int*,int,int*) ; 

__attribute__((used)) static BOOLEAN find_uuid_in_seq (UINT8 *p , UINT32 seq_len, UINT8 *p_uuid,
                                 UINT16 uuid_len, int nest_level)
{
    UINT8   *p_end = p + seq_len;
    UINT8   type;
    UINT32  len;

    /* A little safety check to avoid excessive recursion */
    if (nest_level > 3) {
        return (FALSE);
    }

    while (p < p_end) {
        type = *p++;
        p = sdpu_get_len_from_type (p, type, &len);
        type = type >> 3;
        if (type == UUID_DESC_TYPE) {
            if (sdpu_compare_uuid_arrays (p, len, p_uuid, uuid_len)) {
                return (TRUE);
            }
        } else if (type == DATA_ELE_SEQ_DESC_TYPE) {
            if (find_uuid_in_seq (p, len, p_uuid, uuid_len, nest_level + 1)) {
                return (TRUE);
            }
        }
        p = p + len;
    }

    /* If here, failed to match */
    return (FALSE);
}