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
typedef  int /*<<< orphan*/  u64 ;
struct se_cmd {int dummy; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
#define  PR_TYPE_EXCLUSIVE_ACCESS 133 
#define  PR_TYPE_EXCLUSIVE_ACCESS_ALLREG 132 
#define  PR_TYPE_EXCLUSIVE_ACCESS_REGONLY 131 
#define  PR_TYPE_WRITE_EXCLUSIVE 130 
#define  PR_TYPE_WRITE_EXCLUSIVE_ALLREG 129 
#define  PR_TYPE_WRITE_EXCLUSIVE_REGONLY 128 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  core_scsi3_pro_preempt (struct se_cmd*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,char*,int) ; 

__attribute__((used)) static sense_reason_t
core_scsi3_emulate_pro_preempt(struct se_cmd *cmd, int type, int scope,
		u64 res_key, u64 sa_res_key, int abort)
{
	switch (type) {
	case PR_TYPE_WRITE_EXCLUSIVE:
	case PR_TYPE_EXCLUSIVE_ACCESS:
	case PR_TYPE_WRITE_EXCLUSIVE_REGONLY:
	case PR_TYPE_EXCLUSIVE_ACCESS_REGONLY:
	case PR_TYPE_WRITE_EXCLUSIVE_ALLREG:
	case PR_TYPE_EXCLUSIVE_ACCESS_ALLREG:
		return core_scsi3_pro_preempt(cmd, type, scope, res_key,
					      sa_res_key, abort);
	default:
		pr_err("SPC-3 PR: Unknown Service Action PREEMPT%s"
			" Type: 0x%02x\n", (abort) ? "_AND_ABORT" : "", type);
		return TCM_INVALID_CDB_FIELD;
	}
}