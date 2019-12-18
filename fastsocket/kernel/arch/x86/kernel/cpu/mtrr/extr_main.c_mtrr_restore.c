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
struct sys_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ltype; scalar_t__ lsize; int /*<<< orphan*/  lbase; } ;

/* Variables and functions */
 TYPE_1__* mtrr_value ; 
 int num_var_ranges ; 
 int /*<<< orphan*/  set_mtrr (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mtrr_restore(struct sys_device *sysdev)
{
	int i;

	for (i = 0; i < num_var_ranges; i++) {
		if (mtrr_value[i].lsize) {
			set_mtrr(i, mtrr_value[i].lbase,
				    mtrr_value[i].lsize,
				    mtrr_value[i].ltype,
				    true);
		}
	}
	return 0;
}