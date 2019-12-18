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
struct vx_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SEND_IRQA ; 
 int /*<<< orphan*/  vx_init_rmh (struct vx_rmh*,int /*<<< orphan*/ ) ; 
 int vx_send_msg_nolock (struct vx_core*,struct vx_rmh*) ; 

__attribute__((used)) static int vx_send_irqa(struct vx_core *chip)
{
	struct vx_rmh rmh;

	vx_init_rmh(&rmh, CMD_SEND_IRQA);
	return vx_send_msg_nolock(chip, &rmh); /* no lock needed for trigger */ 
}