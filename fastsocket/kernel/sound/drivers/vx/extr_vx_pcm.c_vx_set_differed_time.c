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
struct vx_rmh {int LgCmd; int /*<<< orphan*/ * Cmd; } ;
struct vx_pipe {int differed_type; int /*<<< orphan*/  pcx_time; } ;
struct vx_core {int dummy; } ;

/* Variables and functions */
 int DC_DIFFERED_DELAY ; 
 int DC_MULTIPLE_DELAY ; 
 int DC_NOTIFY_DELAY ; 
 int DC_STREAM_TIME_DELAY ; 
 int /*<<< orphan*/  DSP_DIFFERED_COMMAND_MASK ; 
 int /*<<< orphan*/  MULTIPLE_MASK_TIME_HIGH ; 
 int /*<<< orphan*/  NOTIFY_MASK_TIME_HIGH ; 
 int /*<<< orphan*/  STREAM_MASK_TIME_HIGH ; 
 int /*<<< orphan*/  vx_set_pcx_time (struct vx_core*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vx_set_differed_time(struct vx_core *chip, struct vx_rmh *rmh,
				struct vx_pipe *pipe)
{
	/* Update The length added to the RMH command by the timestamp */
	if (! (pipe->differed_type & DC_DIFFERED_DELAY))
		return 0;
		
	/* Set the T bit */
	rmh->Cmd[0] |= DSP_DIFFERED_COMMAND_MASK;

	/* Time stamp is the 1st following parameter */
	vx_set_pcx_time(chip, &pipe->pcx_time, &rmh->Cmd[1]);

	/* Add the flags to a notified differed command */
	if (pipe->differed_type & DC_NOTIFY_DELAY)
		rmh->Cmd[1] |= NOTIFY_MASK_TIME_HIGH ;

	/* Add the flags to a multiple differed command */
	if (pipe->differed_type & DC_MULTIPLE_DELAY)
		rmh->Cmd[1] |= MULTIPLE_MASK_TIME_HIGH;

	/* Add the flags to a stream-time differed command */
	if (pipe->differed_type & DC_STREAM_TIME_DELAY)
		rmh->Cmd[1] |= STREAM_MASK_TIME_HIGH;
		
	rmh->LgCmd += 2;
	return 2;
}