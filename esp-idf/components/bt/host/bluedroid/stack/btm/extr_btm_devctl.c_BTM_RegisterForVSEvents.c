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
typedef  int /*<<< orphan*/  tBTM_VS_EVT_CB ;
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  size_t UINT8 ;
struct TYPE_3__ {int /*<<< orphan*/ ** p_vend_spec_cb; } ;
struct TYPE_4__ {TYPE_1__ devcb; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 size_t BTM_MAX_VSE_CALLBACKS ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_EVENT (char*) ; 
 scalar_t__ FALSE ; 
 TYPE_2__ btm_cb ; 

tBTM_STATUS BTM_RegisterForVSEvents (tBTM_VS_EVT_CB *p_cb, BOOLEAN is_register)
{
    tBTM_STATUS retval = BTM_SUCCESS;
    UINT8 i, free_idx = BTM_MAX_VSE_CALLBACKS;

    /* See if callback is already registered */
    for (i = 0; i < BTM_MAX_VSE_CALLBACKS; i++) {
        if (btm_cb.devcb.p_vend_spec_cb[i] == NULL) {
            /* Found a free slot. Store index */
            free_idx = i;
        } else if (btm_cb.devcb.p_vend_spec_cb[i] == p_cb) {
            /* Found callback in lookup table. If deregistering, clear the entry. */
            if (is_register == FALSE) {
                btm_cb.devcb.p_vend_spec_cb[i] = NULL;
                BTM_TRACE_EVENT("BTM Deregister For VSEvents is successfully");
            }
            return (BTM_SUCCESS);
        }
    }

    /* Didn't find callback. Add callback to free slot if registering */
    if (is_register) {
        if (free_idx < BTM_MAX_VSE_CALLBACKS) {
            btm_cb.devcb.p_vend_spec_cb[free_idx] = p_cb;
            BTM_TRACE_EVENT("BTM Register For VSEvents is successfully");
        } else {
            /* No free entries available */
            BTM_TRACE_ERROR ("BTM_RegisterForVSEvents: too many callbacks registered");

            retval = BTM_NO_RESOURCES;
        }
    }

    return (retval);
}