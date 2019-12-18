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
typedef  int /*<<< orphan*/  tBTA_SYS_CONN_CBACK ;
struct TYPE_2__ {int /*<<< orphan*/ * prm_cb; } ;

/* Variables and functions */
 TYPE_1__ bta_sys_cb ; 

void bta_sys_rm_register(tBTA_SYS_CONN_CBACK *p_cback)
{
    bta_sys_cb.prm_cb = p_cback;
}