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
struct TYPE_3__ {scalar_t__ role; int /*<<< orphan*/  local_bda; int /*<<< orphan*/  pairing_bda; } ;
typedef  TYPE_1__ tSMP_CB ;
typedef  int /*<<< orphan*/  tBLE_ADDR_TYPE ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ BT_OCTET16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BDADDR_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_ReadRemoteConnectionAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ HCI_ROLE_MASTER ; 
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  SMP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_debug_print_nbyte_little_endian (scalar_t__,int /*<<< orphan*/  const*,int) ; 

void smp_gen_p2_4_confirm( tSMP_CB *p_cb, BT_OCTET16 p2)
{
    UINT8       *p = (UINT8 *)p2;
    BD_ADDR     remote_bda;
    tBLE_ADDR_TYPE  addr_type = 0;
    SMP_TRACE_DEBUG ("smp_gen_p2_4_confirm\n");
    if (!BTM_ReadRemoteConnectionAddr(p_cb->pairing_bda, remote_bda, &addr_type)) {
        SMP_TRACE_ERROR("can not generate confirm p2 for unknown device\n");
        return;
    }

    SMP_TRACE_DEBUG ("smp_gen_p2_4_confirm\n");

    memset(p, 0, sizeof(BT_OCTET16));

    if (p_cb->role == HCI_ROLE_MASTER) {
        /* LSB ra */
        BDADDR_TO_STREAM(p, remote_bda);
        /* ia */
        BDADDR_TO_STREAM(p, p_cb->local_bda);
    } else {
        /* LSB ra */
        BDADDR_TO_STREAM(p, p_cb->local_bda);
        /* ia */
        BDADDR_TO_STREAM(p, remote_bda);
    }
#if SMP_DEBUG == TRUE
    SMP_TRACE_DEBUG("p2 = padding || ia || ra");
    smp_debug_print_nbyte_little_endian(p2, (const UINT8 *)"p2", 16);
#endif
}