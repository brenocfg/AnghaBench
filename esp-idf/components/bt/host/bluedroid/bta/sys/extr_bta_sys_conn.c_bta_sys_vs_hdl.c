#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_2__ {int /*<<< orphan*/  (* p_vs_evt_hdlr ) (int /*<<< orphan*/ ,void*) ;} ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__ bta_sys_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 

BOOLEAN bta_sys_vs_hdl(UINT16 evt, void *p)
{
    if (bta_sys_cb.p_vs_evt_hdlr) {
        return (*bta_sys_cb.p_vs_evt_hdlr)(evt, p);
    }

    return FALSE;
}