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
struct xt_tgchk_param {struct ipt_log_info* targinfo; } ;
struct ipt_log_info {int level; char* prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static bool log_tg_check(const struct xt_tgchk_param *par)
{
	const struct ipt_log_info *loginfo = par->targinfo;

	if (loginfo->level >= 8) {
		pr_debug("LOG: level %u >= 8\n", loginfo->level);
		return false;
	}
	if (loginfo->prefix[sizeof(loginfo->prefix)-1] != '\0') {
		pr_debug("LOG: prefix term %i\n",
			 loginfo->prefix[sizeof(loginfo->prefix)-1]);
		return false;
	}
	return true;
}