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
typedef  char* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  audit_enabled ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,char*,...) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_release_secctx (char*,char*) ; 
 int security_secid_to_secctx (char*,char**,char**) ; 

__attribute__((used)) static int audit_log_common_recv_msg(struct audit_buffer **ab, u16 msg_type,
				     u32 pid, u32 uid, uid_t auid, u32 ses,
				     u32 sid)
{
	int rc = 0;
	char *ctx = NULL;
	u32 len;

	if (!audit_enabled) {
		*ab = NULL;
		return rc;
	}

	*ab = audit_log_start(NULL, GFP_KERNEL, msg_type);
	audit_log_format(*ab, "user pid=%d uid=%u auid=%u ses=%u",
			 pid, uid, auid, ses);
	if (sid) {
		rc = security_secid_to_secctx(sid, &ctx, &len);
		if (rc)
			audit_log_format(*ab, " ssid=%u", sid);
		else {
			audit_log_format(*ab, " subj=%s", ctx);
			security_release_secctx(ctx, len);
		}
	}

	return rc;
}