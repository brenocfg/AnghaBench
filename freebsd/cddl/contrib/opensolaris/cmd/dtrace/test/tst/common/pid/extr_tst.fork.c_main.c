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
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  go () ; 
 scalar_t__ waiting (int volatile*) ; 

int
main(int argc, char **argv)
{
	volatile int a = 0;

	while (waiting(&a) == 0)
		continue;

	(void) fork();
	(void) go();

	return (0);
}