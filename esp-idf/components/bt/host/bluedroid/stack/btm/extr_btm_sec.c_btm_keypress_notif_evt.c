#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  notif_type; int /*<<< orphan*/ * bd_addr; } ;
typedef  TYPE_2__ tBTM_SP_KEYPRESS ;
typedef  int /*<<< orphan*/  tBTM_SP_EVT_DATA ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_4__ {int /*<<< orphan*/  (* p_sp_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_1__ api; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_SP_KEYPRESS_EVT ; 
 int /*<<< orphan*/  STREAM_TO_BDADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void  btm_keypress_notif_evt (UINT8 *p)
{
    tBTM_SP_KEYPRESS    evt_data;
    UINT8 *p_bda;

    /* parse & report BTM_SP_KEYPRESS_EVT */
    if (btm_cb.api.p_sp_callback) {
        p_bda = evt_data.bd_addr;

        STREAM_TO_BDADDR (p_bda, p);
        evt_data.notif_type = *p;

        (*btm_cb.api.p_sp_callback) (BTM_SP_KEYPRESS_EVT, (tBTM_SP_EVT_DATA *)&evt_data);
    }
}