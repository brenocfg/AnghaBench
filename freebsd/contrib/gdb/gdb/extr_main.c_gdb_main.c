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
struct captured_main_args {int /*<<< orphan*/  use_windows; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  captured_main ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ ,struct captured_main_args*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_windows ; 

int
gdb_main (struct captured_main_args *args)
{
  use_windows = args->use_windows;
  catch_errors (captured_main, args, "", RETURN_MASK_ALL);
  /* The only way to end up here is by an error (normal exit is
     handled by quit_force()), hence always return an error status.  */
  return 1;
}