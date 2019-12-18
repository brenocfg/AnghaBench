#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  SYS_RETURNTOMENU ; 
 int /*<<< orphan*/  SYS_ResetSystem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __exception_closeall () ; 
 scalar_t__ __stub_found () ; 
 int /*<<< orphan*/  reload () ; 

void __reload()
{
	if(__stub_found()) {
		__exception_closeall();
		reload();
	}
	SYS_ResetSystem(SYS_RETURNTOMENU, 0, 0);
}