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
typedef  int /*<<< orphan*/  tBT_UUID ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {int offset; scalar_t__ len; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 scalar_t__ GATT_OP_CODE_SIZE ; 
 int L2CAP_MIN_OFFSET ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ gatt_build_uuid_to_stream (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ osi_malloc (int) ; 

BT_HDR *attp_build_browse_cmd(UINT8 op_code, UINT16 s_hdl, UINT16 e_hdl, tBT_UUID uuid)
{
    BT_HDR      *p_buf = NULL;
    UINT8       *p;

    if ((p_buf = (BT_HDR *)osi_malloc(sizeof(BT_HDR) + 8 + L2CAP_MIN_OFFSET)) != NULL) {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;
        /* Describe the built message location and size */
        p_buf->offset = L2CAP_MIN_OFFSET;
        p_buf->len = GATT_OP_CODE_SIZE + 4;

        UINT8_TO_STREAM (p, op_code);
        UINT16_TO_STREAM (p, s_hdl);
        UINT16_TO_STREAM (p, e_hdl);
        p_buf->len += gatt_build_uuid_to_stream(&p, uuid);
    }

    return p_buf;
}