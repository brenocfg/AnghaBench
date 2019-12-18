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
struct pd_unit {int changed; } ;
typedef  enum action { ____Placeholder_action } action ;

/* Variables and functions */
 int /*<<< orphan*/  DBMSG (char*) ; 
 int ERR_MC ; 
 int /*<<< orphan*/  IDE_ACKCHANGE ; 
 int /*<<< orphan*/  IDE_READ_VRFY ; 
 int Ok ; 
 int STAT_ERR ; 
 int /*<<< orphan*/  STAT_READY ; 
 int /*<<< orphan*/  pd_send_command (struct pd_unit*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pd_wait_for (struct pd_unit*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum action pd_media_check(struct pd_unit *disk)
{
	int r = pd_wait_for(disk, STAT_READY, DBMSG("before media_check"));
	if (!(r & STAT_ERR)) {
		pd_send_command(disk, 1, 1, 0, 0, 0, IDE_READ_VRFY);
		r = pd_wait_for(disk, STAT_READY, DBMSG("RDY after READ_VRFY"));
	} else
		disk->changed = 1;	/* say changed if other error */
	if (r & ERR_MC) {
		disk->changed = 1;
		pd_send_command(disk, 1, 0, 0, 0, 0, IDE_ACKCHANGE);
		pd_wait_for(disk, STAT_READY, DBMSG("RDY after ACKCHANGE"));
		pd_send_command(disk, 1, 1, 0, 0, 0, IDE_READ_VRFY);
		r = pd_wait_for(disk, STAT_READY, DBMSG("RDY after VRFY"));
	}
	return Ok;
}