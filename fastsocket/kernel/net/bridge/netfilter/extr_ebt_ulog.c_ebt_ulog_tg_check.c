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
struct xt_tgchk_param {struct ebt_ulog_info* targinfo; } ;
struct ebt_ulog_info {int nlgroup; char* prefix; scalar_t__ qthreshold; } ;

/* Variables and functions */
 scalar_t__ EBT_ULOG_MAX_QLEN ; 
 int EBT_ULOG_PREFIX_LEN ; 

__attribute__((used)) static bool ebt_ulog_tg_check(const struct xt_tgchk_param *par)
{
	struct ebt_ulog_info *uloginfo = par->targinfo;

	if (uloginfo->nlgroup > 31)
		return false;

	uloginfo->prefix[EBT_ULOG_PREFIX_LEN - 1] = '\0';

	if (uloginfo->qthreshold > EBT_ULOG_MAX_QLEN)
		uloginfo->qthreshold = EBT_ULOG_MAX_QLEN;

	return true;
}