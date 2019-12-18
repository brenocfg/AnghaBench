#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tSDP_RECORD ;
struct TYPE_4__ {scalar_t__ len; int id; } ;
typedef  TYPE_1__ tSDP_ATTRIBUTE ;
typedef  scalar_t__ UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  int UINT16 ;
typedef  int INT32 ;

/* Variables and functions */
 int DATA_ELE_SEQ_DESC_TYPE ; 
 int SIZE_IN_NEXT_BYTE ; 
 int SIZE_IN_NEXT_WORD ; 
 TYPE_1__* sdp_db_find_attr_in_rec (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * sdp_db_find_record (scalar_t__) ; 
 scalar_t__* sdpu_build_attrib_entry (scalar_t__*,TYPE_1__*) ; 

INT32 SDP_ReadRecord(UINT32 handle, UINT8 *p_data, INT32 *p_data_len)
{
    INT32           offset = -1; /* default to not found */
#if SDP_SERVER_ENABLED == TRUE
    INT32           len = 0;                        /* Number of bytes in the entry */
    tSDP_RECORD     *p_rec;
    UINT16          start = 0;
    UINT16          end = 0xffff;
    tSDP_ATTRIBUTE  *p_attr;
    UINT16          rem_len;
    UINT8           *p_rsp;

    /* Find the record in the database */
    p_rec = sdp_db_find_record(handle);
    if (p_rec && p_data && p_data_len) {
        p_rsp = &p_data[3];
        while ( (p_attr = sdp_db_find_attr_in_rec (p_rec, start, end)) != NULL) {
            /* Check if attribute fits. Assume 3-byte value type/length */
            rem_len = *p_data_len - (UINT16) (p_rsp - p_data);

            if (p_attr->len > (UINT32)(rem_len - 6)) {
                break;
            }

            p_rsp = sdpu_build_attrib_entry (p_rsp, p_attr);

            /* next attr id */
            start = p_attr->id + 1;
        }
        len = (INT32) (p_rsp - p_data);

        /* Put in the sequence header (2 or 3 bytes) */
        if (len > 255) {
            offset = 0;
            p_data[0] = (UINT8) ((DATA_ELE_SEQ_DESC_TYPE << 3) | SIZE_IN_NEXT_WORD);
            p_data[1] = (UINT8) ((len - 3) >> 8);
            p_data[2] = (UINT8) (len - 3);
        } else {
            offset = 1;

            p_data[1] = (UINT8) ((DATA_ELE_SEQ_DESC_TYPE << 3) | SIZE_IN_NEXT_BYTE);
            p_data[2] = (UINT8) (len - 3);

            len--;
        }
        *p_data_len = len;
    }
#endif
    /* If here, not found */
    return (offset);
}