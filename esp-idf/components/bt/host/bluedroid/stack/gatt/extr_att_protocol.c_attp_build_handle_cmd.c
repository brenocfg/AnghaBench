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
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {int offset; int len; } ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  GATT_REQ_READ_BLOB ; 
 int L2CAP_MIN_OFFSET ; 
 int /*<<< orphan*/  UINT16_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ osi_malloc (int) ; 

BT_HDR *attp_build_handle_cmd(UINT8 op_code, UINT16 handle, UINT16 offset)
{
    BT_HDR      *p_buf = NULL;
    UINT8       *p;

    if ((p_buf = (BT_HDR *)osi_malloc(sizeof(BT_HDR) + 5 + L2CAP_MIN_OFFSET)) != NULL) {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        p_buf->offset = L2CAP_MIN_OFFSET;

        UINT8_TO_STREAM (p, op_code);
        p_buf->len  = 1;

        UINT16_TO_STREAM (p, handle);
        p_buf->len += 2;

        if (op_code == GATT_REQ_READ_BLOB) {
            UINT16_TO_STREAM (p, offset);
            p_buf->len += 2;
        }

    }

    return p_buf;
}