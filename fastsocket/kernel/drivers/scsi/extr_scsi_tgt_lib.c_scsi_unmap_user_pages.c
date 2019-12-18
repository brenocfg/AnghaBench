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
struct scsi_tgt_cmd {int /*<<< orphan*/  bio; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_rq_unmap_user (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scsi_unmap_user_pages(struct scsi_tgt_cmd *tcmd)
{
	blk_rq_unmap_user(tcmd->bio);
}