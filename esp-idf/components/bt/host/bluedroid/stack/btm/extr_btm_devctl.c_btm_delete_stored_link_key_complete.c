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
struct TYPE_7__ {int /*<<< orphan*/  num_keys; int /*<<< orphan*/  status; int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ tBTM_DELETE_STORED_LINK_KEY_COMPLETE ;
typedef  int /*<<< orphan*/  (* tBTM_CMPL_CB ) (TYPE_2__*) ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_6__ {int /*<<< orphan*/  (* p_stored_link_key_cmpl_cb ) (TYPE_2__*) ;} ;
struct TYPE_8__ {TYPE_1__ devcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_CB_EVT_DELETE_STORED_LINK_KEYS ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__ btm_cb ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void btm_delete_stored_link_key_complete (UINT8 *p)
{
    tBTM_CMPL_CB         *p_cb = btm_cb.devcb.p_stored_link_key_cmpl_cb;
    tBTM_DELETE_STORED_LINK_KEY_COMPLETE  result;

    /* If there was a callback registered for read stored link key, call it */
    btm_cb.devcb.p_stored_link_key_cmpl_cb = NULL;

    if (p_cb) {
        /* Set the call back event to indicate command complete */
        result.event = BTM_CB_EVT_DELETE_STORED_LINK_KEYS;

        /* Extract the result fields from the HCI event */
        STREAM_TO_UINT8  (result.status, p);
        STREAM_TO_UINT16 (result.num_keys, p);

        /* Call the call back and pass the result */
        (*p_cb)(&result);
    }
}