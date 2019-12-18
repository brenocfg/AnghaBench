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
 int /*<<< orphan*/  WIIMOTE_STATE_HANDSHAKE_COMPLETE ; 
 int /*<<< orphan*/  WIIMOTE_STATE_SPEAKER ; 
 int /*<<< orphan*/  WIIMOTE_STATE_SPEAKER_INIT ; 
 int /*<<< orphan*/  WIIUSE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  WM_CMD_SPEAKER_ENABLE ; 
 int /*<<< orphan*/  WM_CMD_SPEAKER_MUTE ; 
 int /*<<< orphan*/  WM_REG_SPEAKER_BLOCK ; 
 int /*<<< orphan*/  WM_REG_SPEAKER_REG1 ; 
 int /*<<< orphan*/  WM_REG_SPEAKER_REG2 ; 
 int /*<<< orphan*/  WM_REG_SPEAKER_REG3 ; 
 int /*<<< orphan*/  __wiiuse_speaker_defconf ; 
 int __wiiuse_speaker_vol ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wiiuse_sendcmd (struct wiimote_t*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiiuse_status (struct wiimote_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiiuse_write_data (struct wiimote_t*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *) ; 

void wiiuse_set_speaker(struct wiimote_t *wm,int status)
{
	ubyte conf[7];
	ubyte buf = 0x00;

	if(!wm) return;

	if(!WIIMOTE_IS_SET(wm,WIIMOTE_STATE_HANDSHAKE_COMPLETE)) {
		WIIUSE_DEBUG("Tried to enable speaker, will wait until handshake finishes.\n");
		if(status)
			WIIMOTE_ENABLE_STATE(wm, WIIMOTE_STATE_SPEAKER_INIT);
		else
			WIIMOTE_DISABLE_STATE(wm, WIIMOTE_STATE_SPEAKER_INIT);
		return;
	}

	if(status) {
		if(WIIMOTE_IS_SET(wm,WIIMOTE_STATE_SPEAKER)) {
			wiiuse_status(wm,NULL);
			return;
		}
	} else {
		if(!WIIMOTE_IS_SET(wm,WIIMOTE_STATE_SPEAKER)) {
			wiiuse_status(wm,NULL);
			return;
		}
	}

	buf = 0x04;
	wiiuse_sendcmd(wm,WM_CMD_SPEAKER_MUTE,&buf,1,NULL);

	if (!status) {
		WIIUSE_DEBUG("Disabled speaker for wiimote id %i.", wm->unid);

		buf = 0x01;
		wiiuse_write_data(wm,WM_REG_SPEAKER_REG1,&buf,1,NULL);

		buf = 0x00;
		wiiuse_write_data(wm,WM_REG_SPEAKER_REG3,&buf,1,NULL);

		buf = 0x00;
		wiiuse_sendcmd(wm,WM_CMD_SPEAKER_ENABLE,&buf,1,NULL);

		wiiuse_status(wm,NULL);
		return;
	}

	memcpy(conf,__wiiuse_speaker_defconf,7);

	buf = 0x04;
	wiiuse_sendcmd(wm,WM_CMD_SPEAKER_ENABLE,&buf,1,NULL);

	buf = 0x01;
	wiiuse_write_data(wm,WM_REG_SPEAKER_REG3,&buf,1,NULL);

	buf = 0x08;
	wiiuse_write_data(wm,WM_REG_SPEAKER_REG1,&buf,1,NULL);

	conf[2] = 0xd0;
	conf[3] = 0x07;
	conf[4] = __wiiuse_speaker_vol;
	wiiuse_write_data(wm,WM_REG_SPEAKER_BLOCK,conf,7,NULL);

	buf = 0x01;
	wiiuse_write_data(wm,WM_REG_SPEAKER_REG2,&buf,1,NULL);

	buf = 0x00;
	wiiuse_sendcmd(wm,WM_CMD_SPEAKER_MUTE,&buf,1,NULL);

	wiiuse_status(wm,NULL);
	return;
}