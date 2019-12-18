#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* upl_t ;
struct upl_io_completion {int dummy; } ;
struct TYPE_3__ {struct upl_io_completion* upl_iodone; } ;

/* Variables and functions */

void upl_set_iodone(upl_t upl, void *upl_iodone)
{
        upl->upl_iodone = (struct upl_io_completion *)upl_iodone;
}