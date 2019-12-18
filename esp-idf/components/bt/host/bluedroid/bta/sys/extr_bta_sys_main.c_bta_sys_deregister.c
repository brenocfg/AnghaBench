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
typedef  size_t UINT8 ;
struct TYPE_2__ {int /*<<< orphan*/ * is_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__ bta_sys_cb ; 

void bta_sys_deregister(UINT8 id)
{
    bta_sys_cb.is_reg[id] = FALSE;
}