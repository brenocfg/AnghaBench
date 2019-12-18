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
struct target_ops {int dummy; } ;
struct mem_attrib {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LWP (int /*<<< orphan*/ ) ; 
 int child_xfer_memory (int /*<<< orphan*/ ,char*,int,int,struct mem_attrib*,struct target_ops*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ is_lwp (int /*<<< orphan*/ ) ; 
 int linux_proc_xfer_memory (int /*<<< orphan*/ ,char*,int,int,struct mem_attrib*,struct target_ops*) ; 
 int /*<<< orphan*/  pid_to_ptid (int /*<<< orphan*/ ) ; 
 struct cleanup* save_inferior_ptid () ; 

__attribute__((used)) static int
lin_lwp_xfer_memory (CORE_ADDR memaddr, char *myaddr, int len, int write,
		     struct mem_attrib *attrib, struct target_ops *target)
{
  struct cleanup *old_chain = save_inferior_ptid ();
  int xfer;

  if (is_lwp (inferior_ptid))
    inferior_ptid = pid_to_ptid (GET_LWP (inferior_ptid));

  xfer = linux_proc_xfer_memory (memaddr, myaddr, len, write, attrib, target);
  if (xfer == 0)
    xfer = child_xfer_memory (memaddr, myaddr, len, write, attrib, target);

  do_cleanups (old_chain);
  return xfer;
}