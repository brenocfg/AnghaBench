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
struct TYPE_6__ {scalar_t__ sec_state; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_7__ {scalar_t__ param; } ;
struct TYPE_8__ {scalar_t__ collision_start_time; scalar_t__ max_collision_delay; TYPE_2__ sec_collision_tle; TYPE_1__* p_collided_dev_rec; } ;

/* Variables and functions */
 scalar_t__ BTM_SEC_INVALID_HANDLE ; 
 scalar_t__ BTM_SEC_STATE_AUTHENTICATING ; 
 scalar_t__ BTM_SEC_STATE_ENCRYPTING ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,scalar_t__) ; 
 int /*<<< orphan*/  BTU_TTYPE_USER_FUNC ; 
 int /*<<< orphan*/  BT_1SEC_TIMEOUT ; 
 TYPE_5__ btm_cb ; 
 TYPE_1__* btm_find_dev_by_handle (scalar_t__) ; 
 scalar_t__ btm_sec_collision_timeout ; 
 TYPE_1__* btm_sec_find_dev_by_sec_state (scalar_t__) ; 
 int /*<<< orphan*/  btu_start_timer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ osi_time_get_os_boottime_ms () ; 

__attribute__((used)) static void btm_sec_auth_collision (UINT16 handle)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    if (!btm_cb.collision_start_time) {
        btm_cb.collision_start_time = osi_time_get_os_boottime_ms();
    }

    if ((osi_time_get_os_boottime_ms() - btm_cb.collision_start_time) < btm_cb.max_collision_delay)
    {
        if (handle == BTM_SEC_INVALID_HANDLE)
        {
            if ((p_dev_rec = btm_sec_find_dev_by_sec_state (BTM_SEC_STATE_AUTHENTICATING)) == NULL) {
                p_dev_rec = btm_sec_find_dev_by_sec_state (BTM_SEC_STATE_ENCRYPTING);
            }
        } else {
            p_dev_rec = btm_find_dev_by_handle (handle);
        }

        if (p_dev_rec != NULL) {
            BTM_TRACE_DEBUG ("btm_sec_auth_collision: state %d (retrying in a moment...)\n", p_dev_rec->sec_state);
            /* We will restart authentication after timeout */
            if (p_dev_rec->sec_state == BTM_SEC_STATE_AUTHENTICATING || p_dev_rec->sec_state == BTM_SEC_STATE_ENCRYPTING) {
                p_dev_rec->sec_state = 0;
            }

            btm_cb.p_collided_dev_rec = p_dev_rec;
            btm_cb.sec_collision_tle.param = (UINT32) btm_sec_collision_timeout;
            btu_start_timer (&btm_cb.sec_collision_tle, BTU_TTYPE_USER_FUNC, BT_1SEC_TIMEOUT);
        }
    }
}