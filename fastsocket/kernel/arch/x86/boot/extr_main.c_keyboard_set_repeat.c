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
struct biosregs {int ax; } ;

/* Variables and functions */
 int /*<<< orphan*/  initregs (struct biosregs*) ; 
 int /*<<< orphan*/  intcall (int,struct biosregs*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void keyboard_set_repeat(void)
{
	struct biosregs ireg;
	initregs(&ireg);
	ireg.ax = 0x0305;
	intcall(0x16, &ireg, NULL);
}