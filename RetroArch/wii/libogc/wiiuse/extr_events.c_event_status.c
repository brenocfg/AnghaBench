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
typedef  int ubyte ;
struct wiimote_t {int battery_level; int /*<<< orphan*/  cmdq; struct cmd_blk_t* cmd_head; int /*<<< orphan*/  event; } ;
struct cmd_blk_t {scalar_t__ state; scalar_t__* data; int /*<<< orphan*/  node; int /*<<< orphan*/  (* cb ) (struct wiimote_t*,int*,int) ;struct cmd_blk_t* next; } ;

/* Variables and functions */
 scalar_t__ CMD_DONE ; 
 scalar_t__ CMD_SENT ; 
 int /*<<< orphan*/  WIIMOTE_DISABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_ENABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ WIIMOTE_IS_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP_FAILED ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP_HANDSHAKE ; 
 int /*<<< orphan*/  WIIMOTE_STATE_IR ; 
 int /*<<< orphan*/  WIIMOTE_STATE_IR_INIT ; 
 int /*<<< orphan*/  WIIMOTE_STATE_SPEAKER ; 
 int /*<<< orphan*/  WIIMOTE_STATE_SPEAKER_INIT ; 
 int /*<<< orphan*/  WIIUSE_STATUS ; 
 scalar_t__ WM_CMD_CTRL_STATUS ; 
 int WM_CTRL_STATUS_BYTE1_ATTACHMENT ; 
 int WM_CTRL_STATUS_BYTE1_IR_ENABLED ; 
 int WM_CTRL_STATUS_BYTE1_SPEAKER_ENABLED ; 
 int /*<<< orphan*/  __lwp_queue_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct wiimote_t*,int*,int) ; 
 int /*<<< orphan*/  wiiuse_disable_expansion (struct wiimote_t*) ; 
 int /*<<< orphan*/  wiiuse_handshake_expansion_start (struct wiimote_t*) ; 
 int /*<<< orphan*/  wiiuse_pressed_buttons (struct wiimote_t*,int*) ; 
 int /*<<< orphan*/  wiiuse_send_next_command (struct wiimote_t*) ; 
 int /*<<< orphan*/  wiiuse_set_ir (struct wiimote_t*,int) ; 
 int /*<<< orphan*/  wiiuse_set_report_type (struct wiimote_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiiuse_set_speaker (struct wiimote_t*,int) ; 

__attribute__((used)) static void event_status(struct wiimote_t *wm,ubyte *msg)
{
	int ir = 0;
	int attachment = 0;
#ifdef HAVE_WIIUSE_SPEAKER
	int speaker = 0;
#endif
	//int led[4]= {0};
	struct cmd_blk_t *cmd = wm->cmd_head;

	wiiuse_pressed_buttons(wm,msg);

	wm->event = WIIUSE_STATUS;
	//if(msg[2]&WM_CTRL_STATUS_BYTE1_LED_1) led[0] = 1;
	//if(msg[2]&WM_CTRL_STATUS_BYTE1_LED_2) led[1] = 1;
	//if(msg[2]&WM_CTRL_STATUS_BYTE1_LED_3) led[2] = 1;
	//if(msg[2]&WM_CTRL_STATUS_BYTE1_LED_4) led[3] = 1;

	if((msg[2]&WM_CTRL_STATUS_BYTE1_ATTACHMENT)==WM_CTRL_STATUS_BYTE1_ATTACHMENT) attachment = 1;
#ifdef HAVE_WIIUSE_SPEAKER
	if((msg[2]&WM_CTRL_STATUS_BYTE1_SPEAKER_ENABLED)==WM_CTRL_STATUS_BYTE1_SPEAKER_ENABLED) speaker = 1;
#endif
	if((msg[2]&WM_CTRL_STATUS_BYTE1_IR_ENABLED)==WM_CTRL_STATUS_BYTE1_IR_ENABLED) ir = 1;

	wm->battery_level = msg[5];

	if(!ir && WIIMOTE_IS_SET(wm,WIIMOTE_STATE_IR_INIT)) {
		WIIMOTE_DISABLE_STATE(wm, WIIMOTE_STATE_IR_INIT);
		wiiuse_set_ir(wm, 1);
		goto done;
	}
	if(ir && !WIIMOTE_IS_SET(wm,WIIMOTE_STATE_IR)) WIIMOTE_ENABLE_STATE(wm,WIIMOTE_STATE_IR);
	else if(!ir && WIIMOTE_IS_SET(wm,WIIMOTE_STATE_IR)) WIIMOTE_DISABLE_STATE(wm, WIIMOTE_STATE_IR);

#ifdef HAVE_WIIUSE_SPEAKER
	if(!speaker && WIIMOTE_IS_SET(wm,WIIMOTE_STATE_SPEAKER_INIT)) {
		WIIMOTE_DISABLE_STATE(wm,WIIMOTE_STATE_SPEAKER_INIT);
		wiiuse_set_speaker(wm,1);
		goto done;
	}
	if(speaker && !WIIMOTE_IS_SET(wm,WIIMOTE_STATE_SPEAKER)) WIIMOTE_ENABLE_STATE(wm,WIIMOTE_STATE_SPEAKER);
	else if(!speaker && WIIMOTE_IS_SET(wm,WIIMOTE_STATE_SPEAKER)) WIIMOTE_DISABLE_STATE(wm,WIIMOTE_STATE_SPEAKER);
#endif

	if(attachment) {
		if(!WIIMOTE_IS_SET(wm,WIIMOTE_STATE_EXP) && !WIIMOTE_IS_SET(wm,WIIMOTE_STATE_EXP_FAILED) && !WIIMOTE_IS_SET(wm,WIIMOTE_STATE_EXP_HANDSHAKE)) {
			wiiuse_handshake_expansion_start(wm);
			goto done;
		}
	} else {
		WIIMOTE_DISABLE_STATE(wm,WIIMOTE_STATE_EXP_FAILED);
		if(WIIMOTE_IS_SET(wm,WIIMOTE_STATE_EXP)) {
			wiiuse_disable_expansion(wm);
			goto done;
		}
	}
	wiiuse_set_report_type(wm,NULL);

done:
	if(!cmd) return;
	if(!(cmd->state==CMD_SENT && cmd->data[0]==WM_CMD_CTRL_STATUS)) return;

	wm->cmd_head = cmd->next;

	cmd->state = CMD_DONE;
	if(cmd->cb!=NULL) cmd->cb(wm,msg,6);

	__lwp_queue_append(&wm->cmdq,&cmd->node);
	wiiuse_send_next_command(wm);
}