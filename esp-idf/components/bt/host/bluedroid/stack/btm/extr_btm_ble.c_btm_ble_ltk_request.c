#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
struct TYPE_8__ {int /*<<< orphan*/  enc_rand; int /*<<< orphan*/  ediv; } ;
typedef  TYPE_2__ tBTM_CB ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ BT_OCTET8 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BT_OCTET8_LEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  btm_ble_ltk_request_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__) ; 
 TYPE_2__ btm_cb ; 
 TYPE_1__* btm_find_dev_by_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_proc_ltk_request (int /*<<< orphan*/ ) ; 

void btm_ble_ltk_request(UINT16 handle, UINT8 rand[8], UINT16 ediv)
{
    tBTM_CB *p_cb = &btm_cb;
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev_by_handle (handle);
    BT_OCTET8 dummy_stk = {0};

    BTM_TRACE_DEBUG ("btm_ble_ltk_request");

    p_cb->ediv = ediv;

    memcpy(p_cb->enc_rand, rand, BT_OCTET8_LEN);

    if (p_dev_rec != NULL) {
        if (!smp_proc_ltk_request(p_dev_rec->bd_addr)) {
            btm_ble_ltk_request_reply(p_dev_rec->bd_addr, FALSE, dummy_stk);
        }
    }

}