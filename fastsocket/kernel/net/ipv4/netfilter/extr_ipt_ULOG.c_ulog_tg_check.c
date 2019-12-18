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
struct xt_tgchk_param {struct ipt_ulog_info* targinfo; } ;
struct ipt_ulog_info {char* prefix; char qthreshold; } ;

/* Variables and functions */
 char ULOG_MAX_QLEN ; 
 int /*<<< orphan*/  pr_debug (char*,char) ; 

__attribute__((used)) static bool ulog_tg_check(const struct xt_tgchk_param *par)
{
	const struct ipt_ulog_info *loginfo = par->targinfo;

	if (loginfo->prefix[sizeof(loginfo->prefix) - 1] != '\0') {
		pr_debug("ipt_ULOG: prefix term %i\n",
			 loginfo->prefix[sizeof(loginfo->prefix) - 1]);
		return false;
	}
	if (loginfo->qthreshold > ULOG_MAX_QLEN) {
		pr_debug("ipt_ULOG: queue threshold %Zu > MAX_QLEN\n",
			 loginfo->qthreshold);
		return false;
	}
	return true;
}