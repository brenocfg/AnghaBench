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
typedef  int /*<<< orphan*/  am_opts ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  apply_opts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_op ; 
 int /*<<< orphan*/  fs_static ; 
 int /*<<< orphan*/  to_free ; 

void
free_opts(am_opts *fo)
{
  /*
   * Copy in the structure we are playing with
   */
  fs_static = *fo;

  /*
   * Free previously allocated memory
   */
  apply_opts(free_op, to_free, FALSE);
}