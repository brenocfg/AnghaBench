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
 int INT_CONF ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void traps(void)
{
	static char test[] __attribute__((aligned(sizeof(int)))) = "CONF";
	int *p = (int *)test;

	if (*p != INT_CONF) {
		fprintf(stderr, "fixdep: sizeof(int) != 4 or wrong endianess? %#x\n",
			*p);
		exit(2);
	}
}