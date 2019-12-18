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
struct TYPE_5__ {int /*<<< orphan*/  status; } ;
struct TYPE_6__ {TYPE_1__ enable; } ;
typedef  TYPE_2__ tBTA_DM_SEC ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_sec_cback ) (int /*<<< orphan*/ ,TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_ENABLE_EVT ; 
 int /*<<< orphan*/  BTA_SUCCESS ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_4__ bta_dm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void bta_dm_local_name_cback(UINT8 *p_name)
{
    tBTA_DM_SEC sec_event;
    UNUSED(p_name);

    sec_event.enable.status = BTA_SUCCESS;

    if (bta_dm_cb.p_sec_cback) {
        bta_dm_cb.p_sec_cback(BTA_DM_ENABLE_EVT, &sec_event);
    }

}