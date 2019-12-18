#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int /*<<< orphan*/  mnt_sb; } ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {scalar_t__ uid; scalar_t__ gid; scalar_t__ mounted_uid; unsigned int file_mode; unsigned int dir_mode; int time_out; unsigned int retry_count; unsigned int flags; int /*<<< orphan*/ * wdog_pid; } ;
struct ncp_server {TYPE_1__ m; } ;

/* Variables and functions */
 int HZ ; 
 unsigned int NCP_DEFAULT_DIR_MODE ; 
 unsigned int NCP_DEFAULT_FILE_MODE ; 
 unsigned int NCP_DEFAULT_RETRY_COUNT ; 
 int NCP_DEFAULT_TIME_OUT ; 
 struct ncp_server* NCP_SBP (int /*<<< orphan*/ ) ; 
 unsigned int S_IALLUGO ; 
 unsigned int pid_vnr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,unsigned int) ; 

__attribute__((used)) static int  ncp_show_options(struct seq_file *seq, struct vfsmount *mnt)
{
	struct ncp_server *server = NCP_SBP(mnt->mnt_sb);
	unsigned int tmp;

	if (server->m.uid != 0)
		seq_printf(seq, ",uid=%u", server->m.uid);
	if (server->m.gid != 0)
		seq_printf(seq, ",gid=%u", server->m.gid);
	if (server->m.mounted_uid != 0)
		seq_printf(seq, ",owner=%u", server->m.mounted_uid);
	tmp = server->m.file_mode & S_IALLUGO;
	if (tmp != NCP_DEFAULT_FILE_MODE)
		seq_printf(seq, ",mode=0%o", tmp);
	tmp = server->m.dir_mode & S_IALLUGO;
	if (tmp != NCP_DEFAULT_DIR_MODE)
		seq_printf(seq, ",dirmode=0%o", tmp);
	if (server->m.time_out != NCP_DEFAULT_TIME_OUT * HZ / 100) {
		tmp = server->m.time_out * 100 / HZ;
		seq_printf(seq, ",timeout=%u", tmp);
	}
	if (server->m.retry_count != NCP_DEFAULT_RETRY_COUNT)
		seq_printf(seq, ",retry=%u", server->m.retry_count);
	if (server->m.flags != 0)
		seq_printf(seq, ",flags=%lu", server->m.flags);
	if (server->m.wdog_pid != NULL)
		seq_printf(seq, ",wdogpid=%u", pid_vnr(server->m.wdog_pid));

	return 0;
}