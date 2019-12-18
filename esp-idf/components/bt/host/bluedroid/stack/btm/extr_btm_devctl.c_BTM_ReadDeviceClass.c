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
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_3__ {scalar_t__ dev_class; } ;
struct TYPE_4__ {TYPE_1__ devcb; } ;

/* Variables and functions */
 TYPE_2__ btm_cb ; 

UINT8 *BTM_ReadDeviceClass (void)
{
    return ((UINT8 *)btm_cb.devcb.dev_class);
}