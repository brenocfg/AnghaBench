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
typedef  int /*<<< orphan*/  uid_t ;
typedef  scalar_t__ u32 ;
struct audit_context {int dummy; } ;
struct audit_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_OBJ_PID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 struct audit_buffer* audit_log_start (struct audit_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_untrustedstring (struct audit_buffer*,char*) ; 
 int /*<<< orphan*/  security_release_secctx (char*,scalar_t__) ; 
 scalar_t__ security_secid_to_secctx (scalar_t__,char**,scalar_t__*) ; 

__attribute__((used)) static int audit_log_pid_context(struct audit_context *context, pid_t pid,
				 uid_t auid, uid_t uid, unsigned int sessionid,
				 u32 sid, char *comm)
{
	struct audit_buffer *ab;
	char *ctx = NULL;
	u32 len;
	int rc = 0;

	ab = audit_log_start(context, GFP_KERNEL, AUDIT_OBJ_PID);
	if (!ab)
		return rc;

	audit_log_format(ab, "opid=%d oauid=%d ouid=%d oses=%d", pid, auid,
			 uid, sessionid);
	if (sid) {
		if (security_secid_to_secctx(sid, &ctx, &len)) {
			audit_log_format(ab, " obj=(none)");
			rc = 1;
		} else {
			audit_log_format(ab, " obj=%s", ctx);
			security_release_secctx(ctx, len);
		}
	}
	audit_log_format(ab, " ocomm=");
	audit_log_untrustedstring(ab, comm);
	audit_log_end(ab);

	return rc;
}