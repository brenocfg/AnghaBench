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
 int /*<<< orphan*/  FPU_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FPU_rm ; 
 int /*<<< orphan*/  REV ; 
 int /*<<< orphan*/  clear_C1 () ; 
 int /*<<< orphan*/  control_word ; 

void fdivr_(void)
{
	/* fdivr st,st(i) */
	clear_C1();
	FPU_div(REV, FPU_rm, control_word);
}