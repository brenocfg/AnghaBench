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
struct audit_watch {int /*<<< orphan*/  path; } ;
struct audit_krule {int /*<<< orphan*/  listnr; int /*<<< orphan*/  filterkey; } ;
struct audit_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_CONFIG_CHANGE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ audit_enabled ; 
 int /*<<< orphan*/  audit_get_loginuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_get_sessionid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_end (struct audit_buffer*) ; 
 int /*<<< orphan*/  audit_log_format (struct audit_buffer*,char*,...) ; 
 int /*<<< orphan*/  audit_log_key (struct audit_buffer*,int /*<<< orphan*/ ) ; 
 struct audit_buffer* audit_log_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_log_string (struct audit_buffer*,char*) ; 
 int /*<<< orphan*/  audit_log_untrustedstring (struct audit_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 

__attribute__((used)) static void audit_watch_log_rule_change(struct audit_krule *r, struct audit_watch *w, char *op)
{
	if (audit_enabled) {
		struct audit_buffer *ab;
		ab = audit_log_start(NULL, GFP_NOFS, AUDIT_CONFIG_CHANGE);
		audit_log_format(ab, "auid=%u ses=%u op=",
				 audit_get_loginuid(current),
				 audit_get_sessionid(current));
		audit_log_string(ab, op);
		audit_log_format(ab, " path=");
		audit_log_untrustedstring(ab, w->path);
		audit_log_key(ab, r->filterkey);
		audit_log_format(ab, " list=%d res=1", r->listnr);
		audit_log_end(ab);
	}
}