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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  outfile ; 
 int /*<<< orphan*/  print_rtx (int /*<<< orphan*/ ) ; 
 scalar_t__ sawclose ; 
 int /*<<< orphan*/  stderr ; 

void
debug_rtx (rtx x)
{
  outfile = stderr;
  sawclose = 0;
  print_rtx (x);
  fprintf (stderr, "\n");
}