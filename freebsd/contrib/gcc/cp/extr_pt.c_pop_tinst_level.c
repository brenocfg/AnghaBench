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
 int /*<<< orphan*/  TINST_IN_SYSTEM_HEADER_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TINST_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_tinst_level ; 
 int /*<<< orphan*/  in_system_header ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  tinst_depth ; 
 int /*<<< orphan*/  tinst_level_tick ; 

__attribute__((used)) static void
pop_tinst_level (void)
{
  tree old = current_tinst_level;

  /* Restore the filename and line number stashed away when we started
     this instantiation.  */
  input_location = TINST_LOCATION (old);
  in_system_header = TINST_IN_SYSTEM_HEADER_P (old);
  current_tinst_level = TREE_CHAIN (old);
  --tinst_depth;
  ++tinst_level_tick;
}