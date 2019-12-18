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
typedef  int /*<<< orphan*/  (* tBTM_CMPL_CB ) (scalar_t__*) ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* p_rln_cmpl_cb ) (scalar_t__*) ;int /*<<< orphan*/  rln_timer; } ;
struct TYPE_4__ {TYPE_1__ devcb; } ;

/* Variables and functions */
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ ) ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  btu_free_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__*) ; 

void btm_read_local_name_complete (UINT8 *p, UINT16 evt_len)
{
    tBTM_CMPL_CB   *p_cb = btm_cb.devcb.p_rln_cmpl_cb;
    UINT8           status;
    UNUSED(evt_len);

    btu_free_timer (&btm_cb.devcb.rln_timer);

    /* If there was a callback address for read local name, call it */
    btm_cb.devcb.p_rln_cmpl_cb = NULL;

    if (p_cb) {
        STREAM_TO_UINT8  (status, p);

        if (status == HCI_SUCCESS) {
            (*p_cb)(p);
        } else {
            (*p_cb)(NULL);
        }
    }
}