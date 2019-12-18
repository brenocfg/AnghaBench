#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ role; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  local_bda; int /*<<< orphan*/  pairing_bda; } ;
typedef  TYPE_1__ tSMP_CB ;
typedef  int /*<<< orphan*/  tBLE_ADDR_TYPE ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ BT_OCTET16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ReadConnectionAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BTM_ReadRemoteConnectionAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ HCI_ROLE_MASTER ; 
 int /*<<< orphan*/  SMP_OPCODE_PAIRING_REQ ; 
 int /*<<< orphan*/  SMP_OPCODE_PAIRING_RSP ; 
 int /*<<< orphan*/  SMP_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  SMP_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  UINT8_TO_STREAM (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_concatenate_local (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_concatenate_peer (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_debug_print_nbyte_little_endian (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

void smp_gen_p1_4_confirm( tSMP_CB *p_cb, BT_OCTET16 p1)
{
    UINT8 *p = (UINT8 *)p1;
    tBLE_ADDR_TYPE    addr_type = 0;
    BD_ADDR           remote_bda;

    SMP_TRACE_DEBUG ("smp_gen_p1_4_confirm\n");

    if (!BTM_ReadRemoteConnectionAddr(p_cb->pairing_bda, remote_bda, &addr_type)) {
        SMP_TRACE_ERROR("can not generate confirm for unknown device\n");
        return;
    }

    BTM_ReadConnectionAddr( p_cb->pairing_bda, p_cb->local_bda, &p_cb->addr_type);

    if (p_cb->role == HCI_ROLE_MASTER) {
        /* LSB : rat': initiator's(local) address type */
        UINT8_TO_STREAM(p, p_cb->addr_type);
        /* LSB : iat': responder's address type */
        UINT8_TO_STREAM(p, addr_type);
        /* concatinate preq */
        smp_concatenate_local(p_cb, &p, SMP_OPCODE_PAIRING_REQ);
        /* concatinate pres */
        smp_concatenate_peer(p_cb, &p, SMP_OPCODE_PAIRING_RSP);
    } else {
        /* LSB : iat': initiator's address type */
        UINT8_TO_STREAM(p, addr_type);
        /* LSB : rat': responder's(local) address type */
        UINT8_TO_STREAM(p, p_cb->addr_type);
        /* concatinate preq */
        smp_concatenate_peer(p_cb, &p, SMP_OPCODE_PAIRING_REQ);
        /* concatinate pres */
        smp_concatenate_local(p_cb, &p, SMP_OPCODE_PAIRING_RSP);
    }
#if SMP_DEBUG == TRUE
    SMP_TRACE_DEBUG("p1 = pres || preq || rat' || iat'\n");
    smp_debug_print_nbyte_little_endian ((UINT8 *)p1, (const UINT8 *)"P1", 16);
#endif
}