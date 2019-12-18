#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* tBTM_CMPL_CB ) (void*) ;
struct TYPE_5__ {int /*<<< orphan*/  (* p_rln_cmpl_cb ) (void*) ;} ;
struct TYPE_7__ {TYPE_1__ devcb; } ;
struct TYPE_6__ {scalar_t__ param; } ;
typedef  scalar_t__ TIMER_PARAM_TYPE ;
typedef  TYPE_2__ TIMER_LIST_ENT ;

/* Variables and functions */
 scalar_t__ TT_DEV_RLN ; 
 TYPE_4__ btm_cb ; 
 int /*<<< orphan*/  stub1 (void*) ; 

void btm_dev_timeout (TIMER_LIST_ENT  *p_tle)
{
    TIMER_PARAM_TYPE timer_type = (TIMER_PARAM_TYPE)p_tle->param;

    if (timer_type == (TIMER_PARAM_TYPE)TT_DEV_RLN) {
        tBTM_CMPL_CB  *p_cb = btm_cb.devcb.p_rln_cmpl_cb;

        btm_cb.devcb.p_rln_cmpl_cb = NULL;

        if (p_cb) {
            (*p_cb)((void *) NULL);
        }
    }
}