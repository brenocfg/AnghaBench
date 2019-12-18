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
struct TYPE_3__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kspd_notifylist ; 
 TYPE_1__ notify ; 
 int /*<<< orphan*/  startwork ; 
 int /*<<< orphan*/  stopwork ; 
 int /*<<< orphan*/  tclimit ; 
 int /*<<< orphan*/  vpe_notify (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int kspd_module_init(void)
{
	INIT_LIST_HEAD(&kspd_notifylist);

	notify.start = startwork;
	notify.stop = stopwork;
	vpe_notify(tclimit, &notify);

	return 0;
}