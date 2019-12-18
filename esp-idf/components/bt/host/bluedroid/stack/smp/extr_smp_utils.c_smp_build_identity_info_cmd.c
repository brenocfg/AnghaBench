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
typedef  int /*<<< orphan*/  tSMP_CB ;
typedef  int /*<<< orphan*/ * UINT8 ;
struct TYPE_3__ {int offset; int len; } ;
typedef  int /*<<< orphan*/  BT_OCTET16 ;
typedef  TYPE_1__ BT_HDR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_TO_STREAM (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_GetDeviceIDRoot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_OCTET16_LEN ; 
 int L2CAP_MIN_OFFSET ; 
 int SMP_ID_INFO_SIZE ; 
 int /*<<< orphan*/  SMP_OPCODE_IDENTITY_INFO ; 
 int /*<<< orphan*/  SMP_TRACE_EVENT (char*) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 scalar_t__ osi_malloc (int) ; 

__attribute__((used)) static BT_HDR *smp_build_identity_info_cmd(UINT8 cmd_code, tSMP_CB *p_cb)
{
    BT_HDR      *p_buf = NULL ;
#if (BLE_INCLUDED == TRUE)
    UINT8       *p;
    BT_OCTET16  irk;
    UNUSED(cmd_code);
    UNUSED(p_cb);

    SMP_TRACE_EVENT("smp_build_identity_info_cmd\n");
    if ((p_buf = (BT_HDR *)osi_malloc(sizeof(BT_HDR) + SMP_ID_INFO_SIZE + L2CAP_MIN_OFFSET)) != NULL) {
        p = (UINT8 *)(p_buf + 1) + L2CAP_MIN_OFFSET;

        BTM_GetDeviceIDRoot(irk);

        UINT8_TO_STREAM (p, SMP_OPCODE_IDENTITY_INFO);
        ARRAY_TO_STREAM (p,  irk, BT_OCTET16_LEN);

        p_buf->offset = L2CAP_MIN_OFFSET;
        p_buf->len = SMP_ID_INFO_SIZE;
    }

#endif  ///BLE_INCLUDED == TRUE
    return p_buf;
}