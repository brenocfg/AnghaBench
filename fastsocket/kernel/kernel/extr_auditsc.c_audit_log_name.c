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
typedef  int /*<<< orphan*/  u32 ;
struct audit_names {int name_len; unsigned long ino; int type; int /*<<< orphan*/  osid; int /*<<< orphan*/  rdev; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; int /*<<< orphan*/  dev; TYPE_1__* name; } ;
struct audit_context {int /*<<< orphan*/  pwd; } ;
struct audit_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  AUDIT_NAME_FULL 132 
 int /*<<< orphan*/  AUDIT_PATH ; 
#define  AUDIT_TYPE_CHILD_CREATE 131 
#define  AUDIT_TYPE_CHILD_DELETE 130 
#define  AUDIT_TYPE_NORMAL 129 
#define  AUDIT_TYPE_PARENT 128 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_d_path (struct audit_buffer*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_fcaps (struct audit_buffer*,struct audit_names*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 int /*<<< orphan*/  audit_log_n_untrustedstring (struct audit_buffer*,int /*<<< orphan*/ ,int) ; 
 struct audit_buffer* audit_log_start (struct audit_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_untrustedstring (struct audit_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  security_release_secctx (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ security_secid_to_secctx (int /*<<< orphan*/ ,char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void audit_log_name(struct audit_context *context, struct audit_names *n,
			   int record_num, int *call_panic)
{
	struct audit_buffer *ab;
	ab = audit_log_start(context, GFP_KERNEL, AUDIT_PATH);
	if (!ab)
		return; /* audit_panic has been called */

	audit_log_format(ab, "item=%d", record_num);

	if (n->name) {
		switch (n->name_len) {
		case AUDIT_NAME_FULL:
			/* log the full path */
			audit_log_format(ab, " name=");
			audit_log_untrustedstring(ab, n->name->name);
			break;
		case 0:
			/* name was specified as a relative path and the
			 * directory component is the cwd */
			audit_log_d_path(ab, "name=", &context->pwd);
			break;
		default:
			/* log the name's directory component */
			audit_log_format(ab, " name=");
			audit_log_n_untrustedstring(ab, n->name->name,
						    n->name_len);
		}
	} else
		audit_log_format(ab, " name=(null)");

	if (n->ino != (unsigned long)-1) {
		audit_log_format(ab, " inode=%lu"
				 " dev=%02x:%02x mode=%#o"
				 " ouid=%u ogid=%u rdev=%02x:%02x",
				 n->ino,
				 MAJOR(n->dev),
				 MINOR(n->dev),
				 n->mode,
				 n->uid,
				 n->gid,
				 MAJOR(n->rdev),
				 MINOR(n->rdev));
	}
	if (n->osid != 0) {
		char *ctx = NULL;
		u32 len;
		if (security_secid_to_secctx(
			n->osid, &ctx, &len)) {
			audit_log_format(ab, " osid=%u", n->osid);
			*call_panic = 2;
		} else {
			audit_log_format(ab, " obj=%s", ctx);
			security_release_secctx(ctx, len);
		}
	}

	/* log the audit_names record type */
	audit_log_format(ab, " nametype=");
	switch(n->type) {
	case AUDIT_TYPE_NORMAL:
		audit_log_format(ab, "NORMAL");
		break;
	case AUDIT_TYPE_PARENT:
		audit_log_format(ab, "PARENT");
		break;
	case AUDIT_TYPE_CHILD_DELETE:
		audit_log_format(ab, "DELETE");
		break;
	case AUDIT_TYPE_CHILD_CREATE:
		audit_log_format(ab, "CREATE");
		break;
	default:
		audit_log_format(ab, "UNKNOWN");
		break;
	}

	audit_log_fcaps(ab, n);

	audit_log_end(ab);
}