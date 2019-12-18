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
struct ps_prochandle {int /*<<< orphan*/  pid; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  ps_err_e ;
typedef  int /*<<< orphan*/  paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PS_ERR ; 
 int /*<<< orphan*/  PS_OK ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  pid_to_ptid (int /*<<< orphan*/ ) ; 
 struct cleanup* save_inferior_ptid () ; 
 int target_read_memory (int /*<<< orphan*/ ,char*,size_t) ; 
 int target_write_memory (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static ps_err_e
ps_xfer_memory (const struct ps_prochandle *ph, paddr_t addr,
		char *buf, size_t len, int write)
{
  struct cleanup *old_chain = save_inferior_ptid ();
  int ret;

  inferior_ptid = pid_to_ptid (ph->pid);

  if (write)
    ret = target_write_memory (addr, buf, len);
  else
    ret = target_read_memory (addr, buf, len);

  do_cleanups (old_chain);

  return (ret == 0 ? PS_OK : PS_ERR);
}