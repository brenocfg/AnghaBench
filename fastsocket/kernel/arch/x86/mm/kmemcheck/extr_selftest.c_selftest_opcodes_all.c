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
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ selftest_opcode_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * selftest_opcodes ; 

__attribute__((used)) static bool selftest_opcodes_all(void)
{
	bool pass = true;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(selftest_opcodes); ++i)
		pass = pass && selftest_opcode_one(&selftest_opcodes[i]);

	return pass;
}