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
 int TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_type_void_data_ptr ; 

__attribute__((used)) static int
procfs_can_use_hw_breakpoint (int type, int cnt, int othertype)
{
#ifndef TARGET_HAS_HARDWARE_WATCHPOINTS
  return 0;
#else
  /* Due to the way that proc_set_watchpoint() is implemented, host
     and target pointers must be of the same size.  If they are not,
     we can't use hardware watchpoints.  This limitation is due to the
     fact that proc_set_watchpoint() calls
     procfs_address_to_host_pointer(); a close inspection of
     procfs_address_to_host_pointer will reveal that an internal error
     will be generated when the host and target pointer sizes are
     different.  */
  if (sizeof (void *) != TYPE_LENGTH (builtin_type_void_data_ptr))
    return 0;

  /* Other tests here???  */

  return 1;
#endif
}