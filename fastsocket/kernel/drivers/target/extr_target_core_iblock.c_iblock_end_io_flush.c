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
struct se_cmd {int dummy; } ;
struct bio {struct se_cmd* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SAM_STAT_GOOD ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iblock_end_io_flush(struct bio *bio, int err)
{
	struct se_cmd *cmd = bio->bi_private;

	if (err)
		pr_err("IBLOCK: cache flush failed: %d\n", err);

	if (cmd) {
		if (err)
			target_complete_cmd(cmd, SAM_STAT_CHECK_CONDITION);
		else
			target_complete_cmd(cmd, SAM_STAT_GOOD);
	}

	bio_put(bio);
}