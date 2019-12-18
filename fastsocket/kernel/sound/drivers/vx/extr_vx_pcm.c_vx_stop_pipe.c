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
struct vx_rmh {int dummy; } ;
struct vx_pipe {int /*<<< orphan*/  number; int /*<<< orphan*/  is_capture; } ;
struct vx_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STOP_PIPE ; 
 int /*<<< orphan*/  vx_init_rmh (struct vx_rmh*,int /*<<< orphan*/ ) ; 
 int vx_send_msg_nolock (struct vx_core*,struct vx_rmh*) ; 
 int /*<<< orphan*/  vx_set_pipe_cmd_params (struct vx_rmh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vx_stop_pipe(struct vx_core *chip, struct vx_pipe *pipe)
{
	struct vx_rmh rmh;
	vx_init_rmh(&rmh, CMD_STOP_PIPE);
	vx_set_pipe_cmd_params(&rmh, pipe->is_capture, pipe->number, 0);
	return vx_send_msg_nolock(chip, &rmh); /* no lock needed for trigger */ 
}