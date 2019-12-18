#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* upl_t ;
struct TYPE_4__ {struct TYPE_4__* associated_upl; } ;

/* Variables and functions */

void upl_set_associated_upl(upl_t upl, upl_t associated_upl)
{
	upl->associated_upl = associated_upl;
}