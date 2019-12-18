#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct audit_buffer {int dummy; } ;
struct TYPE_8__ {unsigned char const* comm; int /*<<< orphan*/  pid; int /*<<< orphan*/  audit_context; } ;
struct TYPE_7__ {int /*<<< orphan*/  uid; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_get_loginuid (TYPE_3__*) ; 
 int /*<<< orphan*/  audit_get_sessionid (TYPE_3__*) ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  audit_log_string (struct audit_buffer*,char const*) ; 
 int /*<<< orphan*/  audit_log_task_context (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_untrustedstring (struct audit_buffer*,unsigned char const*) ; 
 TYPE_3__* current ; 
 TYPE_2__* current_cred () ; 
 int /*<<< orphan*/  ima_audit ; 

void integrity_audit_msg(int audit_msgno, struct inode *inode,
			 const unsigned char *fname, const char *op,
			 const char *cause, int result, int audit_info)
{
	struct audit_buffer *ab;

	if (!ima_audit && audit_info == 1) /* Skip informational messages */
		return;

	ab = audit_log_start(current->audit_context, GFP_KERNEL, audit_msgno);
	audit_log_format(ab, "pid=%d uid=%u auid=%u ses=%u",
			 current->pid, current_cred()->uid,
			 audit_get_loginuid(current),
			 audit_get_sessionid(current));
	audit_log_task_context(ab);
	audit_log_format(ab, " op=");
	audit_log_string(ab, op);
	audit_log_format(ab, " cause=");
	audit_log_string(ab, cause);
	audit_log_format(ab, " comm=");
	audit_log_untrustedstring(ab, current->comm);
	if (fname) {
		audit_log_format(ab, " name=");
		audit_log_untrustedstring(ab, fname);
	}
	if (inode)
		audit_log_format(ab, " dev=%s ino=%lu",
				 inode->i_sb->s_id, inode->i_ino);
	audit_log_format(ab, " res=%d", !result);
	audit_log_end(ab);
}