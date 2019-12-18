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
struct xt_tgchk_param {struct xt_nflog_info* targinfo; } ;
struct xt_nflog_info {int flags; char* prefix; } ;

/* Variables and functions */
 int XT_NFLOG_MASK ; 

__attribute__((used)) static bool nflog_tg_check(const struct xt_tgchk_param *par)
{
	const struct xt_nflog_info *info = par->targinfo;

	if (info->flags & ~XT_NFLOG_MASK)
		return false;
	if (info->prefix[sizeof(info->prefix) - 1] != '\0')
		return false;
	return true;
}