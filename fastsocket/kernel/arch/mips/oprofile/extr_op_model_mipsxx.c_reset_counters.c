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
 int /*<<< orphan*/  w_c0_perfcntr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfcntr1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfcntr2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfcntr3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfctrl0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfctrl1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfctrl2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfctrl3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_counters(void *arg)
{
	int counters = (int)(long)arg;
	switch (counters) {
	case 4:
		w_c0_perfctrl3(0);
		w_c0_perfcntr3(0);
	case 3:
		w_c0_perfctrl2(0);
		w_c0_perfcntr2(0);
	case 2:
		w_c0_perfctrl1(0);
		w_c0_perfcntr1(0);
	case 1:
		w_c0_perfctrl0(0);
		w_c0_perfcntr0(0);
	}
}