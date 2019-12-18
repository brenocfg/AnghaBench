#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
struct TYPE_3__ {int /*<<< orphan*/  (* p_bond_cancel_cmpl_callback ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ api; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ERR_PROCESSING ; 
#define  HCI_ERR_CONNECTION_EXISTS 130 
#define  HCI_ERR_NO_CONNECTION 129 
#define  HCI_SUCCESS 128 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int,int*) ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  btm_sec_bond_cancel_complete () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void btm_create_conn_cancel_complete (UINT8 *p)
{
    UINT8       status;

    STREAM_TO_UINT8 (status, p);
    //BTM_TRACE_EVENT ("btm_create_conn_cancel_complete(): in State: %s  status:%d\n",
    //                 btm_pair_state_descr(btm_cb.pairing_state), status);

    /* if the create conn cancel cmd was issued by the bond cancel,
    ** the application needs to be notified that bond cancel succeeded
    */
    switch (status) {
    case HCI_SUCCESS:
#if (SMP_INCLUDED == TRUE)
        btm_sec_bond_cancel_complete();
#endif  ///SMP_INCLUDED == TRUE
        break;
    case HCI_ERR_CONNECTION_EXISTS:
    case HCI_ERR_NO_CONNECTION:
    default:
        /* Notify application of the error */
        if (btm_cb.api.p_bond_cancel_cmpl_callback) {
            btm_cb.api.p_bond_cancel_cmpl_callback(BTM_ERR_PROCESSING);
        }
        break;
    }
}