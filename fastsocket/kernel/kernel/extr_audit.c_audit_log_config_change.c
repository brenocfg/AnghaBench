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
typedef  int u32 ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_CONFIG_CHANGE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_release_secctx (char*,int) ; 
 int security_secid_to_secctx (int,char**,int*) ; 

__attribute__((used)) static int audit_log_config_change(char *function_name, int new, int old,
				   uid_t loginuid, u32 sessionid, u32 sid,
				   int allow_changes)
{
	struct audit_buffer *ab;
	int rc = 0;

	ab = audit_log_start(NULL, GFP_KERNEL, AUDIT_CONFIG_CHANGE);
	audit_log_format(ab, "%s=%d old=%d auid=%u ses=%u", function_name, new,
			 old, loginuid, sessionid);
	if (sid) {
		char *ctx = NULL;
		u32 len;

		rc = security_secid_to_secctx(sid, &ctx, &len);
		if (rc) {
			audit_log_format(ab, " sid=%u", sid);
			allow_changes = 0; /* Something weird, deny request */
		} else {
			audit_log_format(ab, " subj=%s", ctx);
			security_release_secctx(ctx, len);
		}
	}
	audit_log_format(ab, " res=%d", allow_changes);
	audit_log_end(ab);
	return rc;
}