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
typedef  int /*<<< orphan*/  tSDP_DISC_REC ;
struct TYPE_3__ {int /*<<< orphan*/  p_db; int /*<<< orphan*/  device_address; } ;
typedef  TYPE_1__ tCONN_CB ;
typedef  int UINT8 ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  BE_STREAM_TO_UINT16 (int /*<<< orphan*/ ,int*) ; 
 int DATA_ELE_SEQ_DESC_TYPE ; 
 int /*<<< orphan*/  SDP_TRACE_WARNING (char*,...) ; 
 int UINT_DESC_TYPE ; 
 int* add_attr (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * add_record (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* sdpu_get_len_from_type (int*,int,int*) ; 

__attribute__((used)) static UINT8 *save_attr_seq (tCONN_CB *p_ccb, UINT8 *p, UINT8 *p_msg_end)
{
    UINT32      seq_len, attr_len;
    UINT16      attr_id;
    UINT8       type, *p_seq_end;
    tSDP_DISC_REC *p_rec;

    type = *p++;

    if ((type >> 3) != DATA_ELE_SEQ_DESC_TYPE) {
        SDP_TRACE_WARNING ("SDP - Wrong type: 0x%02x in attr_rsp\n", type);
        return (NULL);
    }

    p = sdpu_get_len_from_type (p, type, &seq_len);
    if ((p + seq_len) > p_msg_end) {
        SDP_TRACE_WARNING ("SDP - Bad len in attr_rsp %d\n", seq_len);
        return (NULL);
    }

    /* Create a record */
    p_rec = add_record (p_ccb->p_db, p_ccb->device_address);
    if (!p_rec) {
        SDP_TRACE_WARNING ("SDP - DB full add_record\n");
        return (NULL);
    }

    p_seq_end = p + seq_len;

    while (p < p_seq_end) {
        /* First get the attribute ID */
        type = *p++;
        p = sdpu_get_len_from_type (p, type, &attr_len);
        if (((type >> 3) != UINT_DESC_TYPE) || (attr_len != 2)) {
            SDP_TRACE_WARNING ("SDP - Bad type: 0x%02x or len: %d in attr_rsp\n", type, attr_len);
            return (NULL);
        }
        BE_STREAM_TO_UINT16 (attr_id, p);

        /* Now, add the attribute value */
        p = add_attr (p, p_ccb->p_db, p_rec, attr_id, NULL, 0);

        if (!p) {
            SDP_TRACE_WARNING ("SDP - DB full add_attr\n");
            return (NULL);
        }
    }

    return (p);
}