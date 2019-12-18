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
struct task_struct {char* comm; } ;
struct seq_file {int dummy; } ;
struct gfs2_holder {scalar_t__ gh_owner_pid; int /*<<< orphan*/  gh_error; int /*<<< orphan*/  gh_iflags; int /*<<< orphan*/  gh_flags; int /*<<< orphan*/  gh_state; int /*<<< orphan*/  gh_ip; } ;

/* Variables and functions */
 int KSYM_SYMBOL_LEN ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  gfs2_print_dbg (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long,char*,char*) ; 
 int /*<<< orphan*/  hflags2str (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pid_nr (scalar_t__) ; 
 struct task_struct* pid_task (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprint_symbol (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state2str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dump_holder(struct seq_file *seq, const struct gfs2_holder *gh)
{
	struct task_struct *gh_owner = NULL;
	char buffer[KSYM_SYMBOL_LEN];
	char flags_buf[32];

	sprint_symbol(buffer, gh->gh_ip);
	if (gh->gh_owner_pid)
		gh_owner = pid_task(gh->gh_owner_pid, PIDTYPE_PID);
	gfs2_print_dbg(seq, " H: s:%s f:%s e:%d p:%ld [%s] %s\n",
		  state2str(gh->gh_state),
		  hflags2str(flags_buf, gh->gh_flags, gh->gh_iflags),
		  gh->gh_error, 
		  gh->gh_owner_pid ? (long)pid_nr(gh->gh_owner_pid) : -1,
		  gh_owner ? gh_owner->comm : "(ended)", buffer);
	return 0;
}