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
struct xt_tgchk_param {struct xt_CHECKSUM_info* targinfo; } ;
struct xt_CHECKSUM_info {int operation; } ;

/* Variables and functions */
 int XT_CHECKSUM_OP_FILL ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static bool checksum_tg_check(const struct xt_tgchk_param *par)
{
	const struct xt_CHECKSUM_info *einfo = par->targinfo;

	if (einfo->operation & ~XT_CHECKSUM_OP_FILL) {
		pr_info("unsupported CHECKSUM operation %x\n", einfo->operation);
		return false;
	}
	if (!einfo->operation) {
		pr_info("no CHECKSUM operation enabled\n");
		return false;
	}
	return true;
}