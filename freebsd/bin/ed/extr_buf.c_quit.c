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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  sfn ; 
 scalar_t__ sfp ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void
quit(int n)
{
	if (sfp) {
		fclose(sfp);
		unlink(sfn);
	}
	exit(n);
}