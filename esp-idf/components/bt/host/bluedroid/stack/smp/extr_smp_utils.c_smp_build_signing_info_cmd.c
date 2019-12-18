#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  csrk; } ;
typedef  TYPE_1__ tSMP_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_6__ {int offset; int len; } ;
typedef  TYPE_2__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_OCTET16_LEN ; 
 int L2CAP_MIN_OFFSET ; 
 int /*<<< orphan*/  SMP_OPCODE_SIGN_INFO ; 
 int SMP_SIGN_INFO_SIZE ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 scalar_t__ osi_malloc (int) ; 

__attribute__((used)) static BT_HDR *smp_build_signing_info_cmd(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR      *p_buf = NULL ;
    UINT8       *p;
    UNUSED(cmd_code);

    SMP_TRACE_EVENT("smp_build_signing_info_cmd\n");
    if ((p_buf = (BT_HDR *)osi_malloc(sizeof(BT_HDR) + SMP_SIGN_INFO_SIZE + L2CAP_MIN_OFFSET)) != NULL) {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        UINT8_TO_STREAM (p, SMP_OPCODE_SIGN_INFO);
        ARRAY_TO_STREAM (p, p_cb->csrk, BT_OCTET16_LEN);

        p_buf->offset = L2CAP_MIN_OFFSET;
        p_buf->len = SMP_SIGN_INFO_SIZE;
    }

    return p_buf;
}