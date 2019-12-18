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
 int /*<<< orphan*/  fo ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void out(int r, int is_last)
{
	if (!is_last)
	{
		fprintf(fo, "    or      $t%i, $t%i, $a2\n", r, r);
		fprintf(fo, "    sb      $t%i, %i($a0)\n", r, r);
	}
	else
	{
		fprintf(fo, "    or      $t%i, $t%i, $a2\n", r, r);
		fprintf(fo, "    jr      $ra\n");
		fprintf(fo, "    sb      $t%i, %i($a0)\n", r, r);
	}
}