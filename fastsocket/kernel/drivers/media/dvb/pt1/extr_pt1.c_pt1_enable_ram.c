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
struct pt1 {TYPE_1__* pdev; } ;
struct TYPE_2__ {int device; } ;

/* Variables and functions */
 int HZ ; 
 int pt1_do_enable_ram (struct pt1*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

__attribute__((used)) static int pt1_enable_ram(struct pt1 *pt1)
{
	int i, ret;
	int phase;
	schedule_timeout_uninterruptible((HZ + 999) / 1000);
	phase = pt1->pdev->device == 0x211a ? 128 : 166;
	for (i = 0; i < phase; i++) {
		ret = pt1_do_enable_ram(pt1);
		if (ret < 0)
			return ret;
	}
	return 0;
}