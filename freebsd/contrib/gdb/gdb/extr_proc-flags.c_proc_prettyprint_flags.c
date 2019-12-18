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
 int /*<<< orphan*/  proc_prettyfprint_flags (int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  stdout ; 

void
proc_prettyprint_flags (unsigned long flags, int verbose)
{
  proc_prettyfprint_flags (stdout, flags, verbose);
}