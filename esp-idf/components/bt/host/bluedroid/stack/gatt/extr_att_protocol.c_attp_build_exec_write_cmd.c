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
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_3__ {int offset; int len; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_DATA_BUF_SIZE ; 
 int GATT_OP_CODE_SIZE ; 
 int /*<<< orphan*/  GATT_PREP_WRITE_EXEC ; 
 int /*<<< orphan*/  GATT_REQ_EXEC_WRITE ; 
 int L2CAP_MIN_OFFSET ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ osi_malloc (int /*<<< orphan*/ ) ; 

BT_HDR *attp_build_exec_write_cmd (UINT8 op_code, UINT8 flag)
{
    BT_HDR      *p_buf = NULL;
    UINT8       *p;

    if ((p_buf = (BT_HDR *)osi_malloc(GATT_DATA_BUF_SIZE)) != NULL) {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        p_buf->offset = L2CAP_MIN_OFFSET;
        p_buf->len = GATT_OP_CODE_SIZE;

        UINT8_TO_STREAM (p, op_code);

        if (op_code == GATT_REQ_EXEC_WRITE) {
            flag &= GATT_PREP_WRITE_EXEC;
            UINT8_TO_STREAM (p, flag);
            p_buf->len += 1;
        }

    }

    return p_buf;
}