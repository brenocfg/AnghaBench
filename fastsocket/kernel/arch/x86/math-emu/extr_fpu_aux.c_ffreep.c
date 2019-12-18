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
 int /*<<< orphan*/  FPU_pop () ; 
 int /*<<< orphan*/  FPU_rm ; 
 int /*<<< orphan*/  FPU_settagi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_Empty ; 

void ffreep(void)
{
	/* ffree st(i) + pop - unofficial code */
	FPU_settagi(FPU_rm, TAG_Empty);
	FPU_pop();
}