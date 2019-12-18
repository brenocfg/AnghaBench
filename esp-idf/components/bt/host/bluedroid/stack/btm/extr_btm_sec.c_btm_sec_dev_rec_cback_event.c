#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pseudo_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  p_ref_data; int /*<<< orphan*/  bd_addr; TYPE_1__ ble; int /*<<< orphan*/  (* p_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  (* tBTM_SEC_CALLBACK ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  BT_TRANSPORT_LE ; 
 int /*<<< orphan*/  btm_sec_check_pending_reqs () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void btm_sec_dev_rec_cback_event (tBTM_SEC_DEV_REC *p_dev_rec, UINT8 res, BOOLEAN is_le_transport)
{
    tBTM_SEC_CALLBACK   *p_callback = p_dev_rec->p_callback;

    if (p_dev_rec->p_callback) {
        p_dev_rec->p_callback = NULL;

#if BLE_INCLUDED == TRUE
        if (is_le_transport) {
            (*p_callback) (p_dev_rec->ble.pseudo_addr, BT_TRANSPORT_LE, p_dev_rec->p_ref_data, res);
        } else
#endif
        {
            (*p_callback) (p_dev_rec->bd_addr, BT_TRANSPORT_BR_EDR, p_dev_rec->p_ref_data, res);
        }
    }
#if (SMP_INCLUDED == TRUE)
    btm_sec_check_pending_reqs();
#endif  ///SMP_INCLUDED == TRUE
}