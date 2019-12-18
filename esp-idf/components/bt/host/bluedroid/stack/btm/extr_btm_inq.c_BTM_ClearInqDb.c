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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_3__ {scalar_t__ inq_active; scalar_t__ inqfilt_active; } ;
typedef  TYPE_1__ tBTM_INQUIRY_VAR_ST ;
struct TYPE_4__ {TYPE_1__ btm_inq_vars; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BUSY ; 
 scalar_t__ BTM_INQUIRY_INACTIVE ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 TYPE_2__ btm_cb ; 
 int /*<<< orphan*/  btm_clr_inq_db (int /*<<< orphan*/ ) ; 

tBTM_STATUS BTM_ClearInqDb (BD_ADDR p_bda)
{
    tBTM_INQUIRY_VAR_ST     *p_inq = &btm_cb.btm_inq_vars;

    /* If an inquiry or remote name is in progress return busy */
    if (p_inq->inq_active != BTM_INQUIRY_INACTIVE ||
            p_inq->inqfilt_active) {
        return (BTM_BUSY);
    }

    btm_clr_inq_db(p_bda);

    return (BTM_SUCCESS);
}