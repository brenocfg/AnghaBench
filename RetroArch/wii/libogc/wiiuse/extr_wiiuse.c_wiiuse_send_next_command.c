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
struct wiimote_t {struct cmd_blk_t* cmd_head; } ;
struct cmd_blk_t {scalar_t__ state; int* data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 scalar_t__ CMD_READY ; 
 scalar_t__ CMD_SENT ; 
 int /*<<< orphan*/  WIIMOTE_IS_CONNECTED (struct wiimote_t*) ; 
 scalar_t__ WIIMOTE_IS_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_RUMBLE ; 
 int /*<<< orphan*/  wiiuse_io_write (struct wiimote_t*,int*,int /*<<< orphan*/ ) ; 

void wiiuse_send_next_command(struct wiimote_t *wm)
{
	struct cmd_blk_t *cmd = wm->cmd_head;

	if(!wm || !WIIMOTE_IS_CONNECTED(wm)) return;

	if(!cmd) return;
	if(cmd->state!=CMD_READY) return;

	cmd->state = CMD_SENT;
#ifdef HAVE_WIIUSE_RUMBLE
	if(WIIMOTE_IS_SET(wm,WIIMOTE_STATE_RUMBLE)) cmd->data[1] |= 0x01;
#endif

	//WIIUSE_DEBUG("Sending command: %02x %02x", cmd->data[0], cmd->data[1]);
	wiiuse_io_write(wm,cmd->data,cmd->len);
}