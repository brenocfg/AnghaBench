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
struct scsi_cmnd {int dummy; } ;
struct request {struct scsi_cmnd* special; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_unprep_request (struct request*) ; 
 int /*<<< orphan*/  scsi_put_command (struct scsi_cmnd*) ; 

__attribute__((used)) static void scsi_unprep_request(struct request *req)
{
	struct scsi_cmnd *cmd = req->special;

	blk_unprep_request(req);
	req->special = NULL;

	scsi_put_command(cmd);
}