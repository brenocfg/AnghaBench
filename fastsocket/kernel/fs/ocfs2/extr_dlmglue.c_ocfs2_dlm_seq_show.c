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
struct seq_file {int dummy; } ;
struct ocfs2_lock_res {scalar_t__ l_type; int /*<<< orphan*/  l_lksb; int /*<<< orphan*/  l_blocking; int /*<<< orphan*/  l_requested; int /*<<< orphan*/  l_ex_holders; int /*<<< orphan*/  l_ro_holders; int /*<<< orphan*/  l_unlock_action; int /*<<< orphan*/  l_action; int /*<<< orphan*/  l_flags; int /*<<< orphan*/  l_level; int /*<<< orphan*/  l_name; } ;

/* Variables and functions */
 int DLM_LVB_LEN ; 
 int EINVAL ; 
 scalar_t__ OCFS2_DENTRY_LOCK_INO_START ; 
 int /*<<< orphan*/  OCFS2_DLM_DEBUG_STR_VERSION ; 
 int /*<<< orphan*/  OCFS2_LOCK_ID_MAX_LEN ; 
 scalar_t__ OCFS2_LOCK_TYPE_DENTRY ; 
 int /*<<< orphan*/  lock_max_exmode (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  lock_max_prmode (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  lock_num_exmode (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  lock_num_exmode_failed (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  lock_num_prmode (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  lock_num_prmode_failed (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  lock_refresh (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  lock_total_exmode (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  lock_total_prmode (struct ocfs2_lock_res*) ; 
 char* ocfs2_dlm_lvb (int /*<<< orphan*/ *) ; 
 scalar_t__ ocfs2_get_dentry_lock_ino (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static int ocfs2_dlm_seq_show(struct seq_file *m, void *v)
{
	int i;
	char *lvb;
	struct ocfs2_lock_res *lockres = v;

	if (!lockres)
		return -EINVAL;

	seq_printf(m, "0x%x\t", OCFS2_DLM_DEBUG_STR_VERSION);

	if (lockres->l_type == OCFS2_LOCK_TYPE_DENTRY)
		seq_printf(m, "%.*s%08x\t", OCFS2_DENTRY_LOCK_INO_START - 1,
			   lockres->l_name,
			   (unsigned int)ocfs2_get_dentry_lock_ino(lockres));
	else
		seq_printf(m, "%.*s\t", OCFS2_LOCK_ID_MAX_LEN, lockres->l_name);

	seq_printf(m, "%d\t"
		   "0x%lx\t"
		   "0x%x\t"
		   "0x%x\t"
		   "%u\t"
		   "%u\t"
		   "%d\t"
		   "%d\t",
		   lockres->l_level,
		   lockres->l_flags,
		   lockres->l_action,
		   lockres->l_unlock_action,
		   lockres->l_ro_holders,
		   lockres->l_ex_holders,
		   lockres->l_requested,
		   lockres->l_blocking);

	/* Dump the raw LVB */
	lvb = ocfs2_dlm_lvb(&lockres->l_lksb);
	for(i = 0; i < DLM_LVB_LEN; i++)
		seq_printf(m, "0x%x\t", lvb[i]);

#ifdef CONFIG_OCFS2_FS_STATS
# define lock_num_prmode(_l)		(_l)->l_lock_num_prmode
# define lock_num_exmode(_l)		(_l)->l_lock_num_exmode
# define lock_num_prmode_failed(_l)	(_l)->l_lock_num_prmode_failed
# define lock_num_exmode_failed(_l)	(_l)->l_lock_num_exmode_failed
# define lock_total_prmode(_l)		(_l)->l_lock_total_prmode
# define lock_total_exmode(_l)		(_l)->l_lock_total_exmode
# define lock_max_prmode(_l)		(_l)->l_lock_max_prmode
# define lock_max_exmode(_l)		(_l)->l_lock_max_exmode
# define lock_refresh(_l)		(_l)->l_lock_refresh
#else
# define lock_num_prmode(_l)		(0ULL)
# define lock_num_exmode(_l)		(0ULL)
# define lock_num_prmode_failed(_l)	(0)
# define lock_num_exmode_failed(_l)	(0)
# define lock_total_prmode(_l)		(0ULL)
# define lock_total_exmode(_l)		(0ULL)
# define lock_max_prmode(_l)		(0)
# define lock_max_exmode(_l)		(0)
# define lock_refresh(_l)		(0)
#endif
	/* The following seq_print was added in version 2 of this output */
	seq_printf(m, "%llu\t"
		   "%llu\t"
		   "%u\t"
		   "%u\t"
		   "%llu\t"
		   "%llu\t"
		   "%u\t"
		   "%u\t"
		   "%u\t",
		   lock_num_prmode(lockres),
		   lock_num_exmode(lockres),
		   lock_num_prmode_failed(lockres),
		   lock_num_exmode_failed(lockres),
		   lock_total_prmode(lockres),
		   lock_total_exmode(lockres),
		   lock_max_prmode(lockres),
		   lock_max_exmode(lockres),
		   lock_refresh(lockres));

	/* End the line */
	seq_printf(m, "\n");
	return 0;
}