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
struct TYPE_3__ {int inq_active; scalar_t__ state; scalar_t__ no_inc_ssp; int /*<<< orphan*/  inqfilt_active; } ;
struct TYPE_4__ {TYPE_1__ btm_inq_vars; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_CancelPeriodicInquiry () ; 
 int BTM_GENERAL_INQUIRY_ACTIVE ; 
 scalar_t__ BTM_INQ_ACTIVE_STATE ; 
 int BTM_LIMITED_INQUIRY_ACTIVE ; 
 int BTM_PERIODIC_INQUIRY_ACTIVE ; 
 int BTM_SSP_INQUIRY_ACTIVE ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_inq_cancel () ; 

void btm_inq_stop_on_ssp(void)
{
    UINT8 normal_active = (BTM_GENERAL_INQUIRY_ACTIVE | BTM_LIMITED_INQUIRY_ACTIVE);

#if (BTM_INQ_DEBUG == TRUE)
    BTM_TRACE_DEBUG ("btm_inq_stop_on_ssp: no_inc_ssp=%d inq_active:0x%x state:%d inqfilt_active:%d\n",
                     btm_cb.btm_inq_vars.no_inc_ssp, btm_cb.btm_inq_vars.inq_active, btm_cb.btm_inq_vars.state, btm_cb.btm_inq_vars.inqfilt_active);
#endif
    if (btm_cb.btm_inq_vars.no_inc_ssp) {
        if (btm_cb.btm_inq_vars.state == BTM_INQ_ACTIVE_STATE) {
            if (btm_cb.btm_inq_vars.inq_active & BTM_PERIODIC_INQUIRY_ACTIVE) {
                BTM_CancelPeriodicInquiry();
            } else if (btm_cb.btm_inq_vars.inq_active & normal_active) {
                /* can not call BTM_CancelInquiry() here. We need to report inquiry complete evt */
                btsnd_hcic_inq_cancel();
            }
        }
        /* do not allow inquiry to start */
        btm_cb.btm_inq_vars.inq_active |= BTM_SSP_INQUIRY_ACTIVE;
    }
}