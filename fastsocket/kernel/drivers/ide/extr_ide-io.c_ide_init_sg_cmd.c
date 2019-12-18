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
struct ide_cmd {unsigned int nbytes; unsigned int nleft; int /*<<< orphan*/ * cursg; scalar_t__ cursg_ofs; } ;

/* Variables and functions */

void ide_init_sg_cmd(struct ide_cmd *cmd, unsigned int nr_bytes)
{
	cmd->nbytes = cmd->nleft = nr_bytes;
	cmd->cursg_ofs = 0;
	cmd->cursg = NULL;
}