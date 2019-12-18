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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int estimate_num_insns (int /*<<< orphan*/ ) ; 
 int optimize ; 
 scalar_t__ optimize_size ; 

__attribute__((used)) static bool
decide_copy_try_finally (int ndests, tree finally)
{
  int f_estimate, sw_estimate;

  if (!optimize)
    return false;

  /* Finally estimate N times, plus N gotos.  */
  f_estimate = estimate_num_insns (finally);
  f_estimate = (f_estimate + 1) * ndests;

  /* Switch statement (cost 10), N variable assignments, N gotos.  */
  sw_estimate = 10 + 2 * ndests;

  /* Optimize for size clearly wants our best guess.  */
  if (optimize_size)
    return f_estimate < sw_estimate;

  /* ??? These numbers are completely made up so far.  */
  if (optimize > 1)
    return f_estimate < 100 || f_estimate < sw_estimate * 2;
  else
    return f_estimate < 40 || f_estimate * 2 < sw_estimate * 3;
}