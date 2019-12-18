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
struct wiimote_t {int /*<<< orphan*/  unid; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIIMOTE_DISABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_ENABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ WIIMOTE_IS_SET (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP ; 
 int /*<<< orphan*/  WIIMOTE_STATE_HANDSHAKE_COMPLETE ; 
 int /*<<< orphan*/  WIIMOTE_STATE_IR ; 
 int /*<<< orphan*/  WIIMOTE_STATE_IR_INIT ; 
 int /*<<< orphan*/  WIIUSE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  WIIUSE_ERROR (char*) ; 
 int /*<<< orphan*/  WM_CMD_IR ; 
 int /*<<< orphan*/  WM_CMD_IR_2 ; 
 int WM_IR_TYPE_BASIC ; 
 int WM_IR_TYPE_EXTENDED ; 
 int /*<<< orphan*/  WM_REG_IR ; 
 int /*<<< orphan*/  WM_REG_IR_BLOCK1 ; 
 int /*<<< orphan*/  WM_REG_IR_BLOCK2 ; 
 int /*<<< orphan*/  WM_REG_IR_MODENUM ; 
 int get_ir_sens (struct wiimote_t*,char**,char**) ; 
 int /*<<< orphan*/  wiiuse_sendcmd (struct wiimote_t*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiiuse_status (struct wiimote_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiiuse_write_data (struct wiimote_t*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *) ; 

void wiiuse_set_ir(struct wiimote_t *wm,int status)
{
	ubyte buf = 0x00;
	int ir_level = 0;
	char* block1 = NULL;
	char* block2 = NULL;

	if(!wm) return;

	/*
	 *	Wait for the handshake to finish first.
	 *	When it handshake finishes and sees that
	 *	IR is enabled, it will call this function
	 *	again to actually enable IR.
	 */
	if(!WIIMOTE_IS_SET(wm,WIIMOTE_STATE_HANDSHAKE_COMPLETE)) {
		WIIUSE_DEBUG("Tried to enable IR, will wait until handshake finishes.\n");
		if(status)
			WIIMOTE_ENABLE_STATE(wm, WIIMOTE_STATE_IR_INIT);
		else
			WIIMOTE_DISABLE_STATE(wm, WIIMOTE_STATE_IR_INIT);
		return;
	}

	/*
	 *	Check to make sure a sensitivity setting is selected.
	 */
	ir_level = get_ir_sens(wm, &block1, &block2);
	if (!ir_level) {
		WIIUSE_ERROR("No IR sensitivity setting selected.");
		return;
	}

	if (status) {
		/* if already enabled then stop */
		if (WIIMOTE_IS_SET(wm, WIIMOTE_STATE_IR)) {
			wiiuse_status(wm,NULL);
			return;
		}
	} else {
		/* if already disabled then stop */
		if (!WIIMOTE_IS_SET(wm, WIIMOTE_STATE_IR)) {
			wiiuse_status(wm,NULL);
			return;
		}
	}

	buf = (status ? 0x04 : 0x00);
	wiiuse_sendcmd(wm,WM_CMD_IR,&buf,1,NULL);
	wiiuse_sendcmd(wm,WM_CMD_IR_2,&buf,1,NULL);

	if (!status) {
		WIIUSE_DEBUG("Disabled IR cameras for wiimote id %i.", wm->unid);
		wiiuse_status(wm,NULL);
		return;
	}

	/* enable IR, set sensitivity */
	buf = 0x08;
	wiiuse_write_data(wm,WM_REG_IR,&buf,1,NULL);

	wiiuse_write_data(wm, WM_REG_IR_BLOCK1, (ubyte*)block1, 9, NULL);
	wiiuse_write_data(wm, WM_REG_IR_BLOCK2, (ubyte*)block2, 2, NULL);

	if(WIIMOTE_IS_SET(wm,WIIMOTE_STATE_EXP)) buf = WM_IR_TYPE_BASIC;
	else buf = WM_IR_TYPE_EXTENDED;
	wiiuse_write_data(wm,WM_REG_IR_MODENUM, &buf, 1, NULL);

	wiiuse_status(wm,NULL);
	return;
}