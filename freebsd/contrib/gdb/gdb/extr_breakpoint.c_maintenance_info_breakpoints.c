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
 int /*<<< orphan*/  breakpoint_1 (int,int) ; 
 int parse_and_eval_long (char*) ; 

__attribute__((used)) static void
maintenance_info_breakpoints (char *bnum_exp, int from_tty)
{
  int bnum = -1;

  if (bnum_exp)
    bnum = parse_and_eval_long (bnum_exp);

  breakpoint_1 (bnum, 1);
}