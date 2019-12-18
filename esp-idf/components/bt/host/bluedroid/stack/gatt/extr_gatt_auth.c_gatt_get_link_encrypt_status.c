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
struct TYPE_3__ {int /*<<< orphan*/  transport; int /*<<< orphan*/  peer_bda; } ;
typedef  TYPE_1__ tGATT_TCB ;
typedef  int /*<<< orphan*/  tGATT_STATUS ;
typedef  int UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_GetSecurityFlagsByTransport (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int BTM_SEC_FLAG_ENCRYPTED ; 
 int BTM_SEC_FLAG_LKEY_AUTHED ; 
 int BTM_SEC_FLAG_LKEY_KNOWN ; 
 int /*<<< orphan*/  GATT_ENCRYPED_MITM ; 
 int /*<<< orphan*/  GATT_ENCRYPED_NO_MITM ; 
 int /*<<< orphan*/  GATT_NOT_ENCRYPTED ; 
 int /*<<< orphan*/  GATT_TRACE_DEBUG (char*,int /*<<< orphan*/ ) ; 

tGATT_STATUS gatt_get_link_encrypt_status(tGATT_TCB *p_tcb)
{
    tGATT_STATUS    encrypt_status = GATT_NOT_ENCRYPTED;
    UINT8           sec_flag = 0;

    BTM_GetSecurityFlagsByTransport(p_tcb->peer_bda, &sec_flag, p_tcb->transport);

    if ((sec_flag & BTM_SEC_FLAG_ENCRYPTED) && (sec_flag & BTM_SEC_FLAG_LKEY_KNOWN)) {
        encrypt_status = GATT_ENCRYPED_NO_MITM;
        if (sec_flag & BTM_SEC_FLAG_LKEY_AUTHED) {
            encrypt_status = GATT_ENCRYPED_MITM;
        }
    }

    GATT_TRACE_DEBUG("gatt_get_link_encrypt_status status=0x%x", encrypt_status);
    return  encrypt_status ;
}