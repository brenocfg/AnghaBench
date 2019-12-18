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
typedef  int /*<<< orphan*/  u32 ;
struct se_session {int dummy; } ;
struct se_cmd {int dummy; } ;

/* Variables and functions */
 int target_submit_cmd_map_sgls (struct se_cmd*,struct se_session*,unsigned char*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int target_submit_cmd(struct se_cmd *se_cmd, struct se_session *se_sess,
		unsigned char *cdb, unsigned char *sense, u32 unpacked_lun,
		u32 data_length, int task_attr, int data_dir, int flags)
{
	return target_submit_cmd_map_sgls(se_cmd, se_sess, cdb, sense,
			unpacked_lun, data_length, task_attr, data_dir,
			flags, NULL, 0, NULL, 0);
}