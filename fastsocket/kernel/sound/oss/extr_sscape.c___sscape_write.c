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
 int /*<<< orphan*/  ODIE_ADDR ; 
 int /*<<< orphan*/  ODIE_DATA ; 
 int /*<<< orphan*/  PORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __sscape_write(int reg, int data)
{
	outb(reg, PORT(ODIE_ADDR));
	outb(data, PORT(ODIE_DATA));
}