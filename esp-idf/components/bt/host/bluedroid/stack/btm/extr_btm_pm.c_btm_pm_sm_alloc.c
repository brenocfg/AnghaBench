#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ tBTM_PM_MCB ;
typedef  size_t UINT8 ;
struct TYPE_5__ {TYPE_1__* pm_mode_db; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_PM_ST_ACTIVE ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,size_t,int /*<<< orphan*/ ) ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void btm_pm_sm_alloc(UINT8 ind)
{
    tBTM_PM_MCB *p_db = &btm_cb.pm_mode_db[ind];   /* per ACL link */
    memset (p_db, 0, sizeof(tBTM_PM_MCB));
    p_db->state = BTM_PM_ST_ACTIVE;
#if BTM_PM_DEBUG == TRUE
    BTM_TRACE_DEBUG( "btm_pm_sm_alloc ind:%d st:%d", ind, p_db->state);
#endif  // BTM_PM_DEBUG
}