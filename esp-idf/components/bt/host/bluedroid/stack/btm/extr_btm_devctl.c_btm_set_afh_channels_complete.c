#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int hci_status; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ tBTM_SET_AFH_CHANNELS_RESULTS ;
typedef  int /*<<< orphan*/  (* tBTM_CMPL_CB ) (TYPE_2__*) ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_6__ {int /*<<< orphan*/  (* p_afh_channels_cmpl_cb ) (TYPE_2__*) ;int /*<<< orphan*/  afh_channels_timer; } ;
struct TYPE_8__ {TYPE_1__ devcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_ERR_PROCESSING ; 
 int /*<<< orphan*/  BTM_ILLEGAL_VALUE ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
#define  HCI_ERR_ILLEGAL_PARAMETER_FMT 130 
#define  HCI_ERR_UNSUPPORTED_VALUE 129 
#define  HCI_SUCCESS 128 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int,int /*<<< orphan*/ *) ; 
 TYPE_5__ btm_cb ; 
 int /*<<< orphan*/  btu_free_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void btm_set_afh_channels_complete (UINT8 *p)
{
    tBTM_CMPL_CB *p_cb = btm_cb.devcb.p_afh_channels_cmpl_cb;
    tBTM_SET_AFH_CHANNELS_RESULTS results;

    btu_free_timer (&btm_cb.devcb.afh_channels_timer);

    /* If there is a callback address for setting AFH channels, call it */
    btm_cb.devcb.p_afh_channels_cmpl_cb = NULL;

    if (p_cb) {
        STREAM_TO_UINT8 (results.hci_status, p);

        switch (results.hci_status){
            case HCI_SUCCESS:
                results.status = BTM_SUCCESS;
                break;
            case HCI_ERR_UNSUPPORTED_VALUE:
            case HCI_ERR_ILLEGAL_PARAMETER_FMT:
                results.status = BTM_ILLEGAL_VALUE;
                break;
            default:
                results.status = BTM_ERR_PROCESSING;
                break;
        }
        (*p_cb)(&results);
    }
}