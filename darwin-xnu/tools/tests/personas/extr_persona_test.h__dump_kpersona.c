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
typedef  int uint32_t ;
struct kpersona_info {int persona_ngroups; int /*<<< orphan*/  persona_name; scalar_t__ persona_gmuid; int /*<<< orphan*/ * persona_groups; int /*<<< orphan*/  persona_gid; int /*<<< orphan*/  persona_type; int /*<<< orphan*/  persona_id; int /*<<< orphan*/  persona_info_version; } ;

/* Variables and functions */
 int PA_HAS_GID ; 
 int PA_HAS_GROUPS ; 
 int PA_HAS_ID ; 
 int PA_HAS_LOGIN ; 
 int PA_HAS_TYPE ; 
 int /*<<< orphan*/  info (char*,...) ; 
 int /*<<< orphan*/  info_cont (char*,...) ; 
 int /*<<< orphan*/  info_end () ; 
 int /*<<< orphan*/  info_start (char*,int) ; 

__attribute__((used)) static inline void _dump_kpersona(const char *msg, uint32_t flags, const struct kpersona_info *ki)
{
	if (msg)
		info("%s", msg);
	info("\t kpersona_info (v%d) {", ki->persona_info_version);
	info("\t\t     %cid:  %d", flags & PA_HAS_ID ? '+' : '-', ki->persona_id);
	info("\t\t     %ctype:  %d", flags & PA_HAS_TYPE ? '+' : '-', ki->persona_type);
	info("\t\t    %cgid:  %d", flags & PA_HAS_GID ? '+' : '-', ki->persona_gid);

	info_start("\t\t  ngroups:  %d", ki->persona_ngroups);
	for (int i = 0; i < ki->persona_ngroups; i++) {
		if (i == 0) info_cont(" {");
		info_cont(" %d", ki->persona_groups[i]);
	}
	if (ki->persona_ngroups > 0)
		info_cont(" }");
	info_end();

	info("\t\t  %cgmuid: %d (0x%x)", flags & PA_HAS_GROUPS ? '+' : '-',
	     (int)ki->persona_gmuid, ki->persona_gmuid);
	info("\t\t  %clogin: \"%s\"", flags & PA_HAS_LOGIN ? '+' : '-', ki->persona_name);
	info("\t }");
}