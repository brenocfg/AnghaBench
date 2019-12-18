#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uword ;
typedef  int ubyte ;
struct TYPE_2__ {int /*<<< orphan*/  classic; int /*<<< orphan*/  nunchuk; } ;
struct wiimote_t {int expansion_state; TYPE_1__ exp; } ;

/* Variables and functions */
 int BIG_ENDIAN_LONG (int) ; 
 int EXP_HANDSHAKE_LEN ; 
#define  EXP_ID_CODE_CLASSIC_CONTROLLER 138 
#define  EXP_ID_CODE_CLASSIC_CONTROLLER_GENERIC 137 
#define  EXP_ID_CODE_CLASSIC_CONTROLLER_GENERIC2 136 
#define  EXP_ID_CODE_CLASSIC_CONTROLLER_GENERIC3 135 
#define  EXP_ID_CODE_CLASSIC_CONTROLLER_GENERIC4 134 
#define  EXP_ID_CODE_CLASSIC_CONTROLLER_GENERIC5 133 
#define  EXP_ID_CODE_CLASSIC_CONTROLLER_NYKOWING 132 
#define  EXP_ID_CODE_CLASSIC_CONTROLLER_NYKOWING2 131 
#define  EXP_ID_CODE_CLASSIC_CONTROLLER_NYKOWING3 130 
#define  EXP_ID_CODE_CLASSIC_WIIU_PRO 129 
#define  EXP_ID_CODE_NUNCHUK 128 
 int /*<<< orphan*/  WIIMOTE_DISABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_ENABLE_STATE (struct wiimote_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP ; 
 int /*<<< orphan*/  WIIMOTE_STATE_EXP_HANDSHAKE ; 
 int /*<<< orphan*/  WM_EXP_MEM_CALIBR ; 
 int /*<<< orphan*/  WM_EXP_MEM_ENABLE1 ; 
 int /*<<< orphan*/  WM_EXP_MEM_ENABLE2 ; 
 int* __lwp_wkspace_allocate (int) ; 
 int /*<<< orphan*/  __lwp_wkspace_free (int*) ; 
 int /*<<< orphan*/  classic_ctrl_handshake (struct wiimote_t*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nunchuk_handshake (struct wiimote_t*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiiuse_read_data (struct wiimote_t*,int*,int /*<<< orphan*/ ,int,void (*) (struct wiimote_t*,int*,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  wiiuse_set_ir_mode (struct wiimote_t*) ; 
 int /*<<< orphan*/  wiiuse_status (struct wiimote_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiiuse_write_data (struct wiimote_t*,int /*<<< orphan*/ ,int*,int,void (*) (struct wiimote_t*,int*,int /*<<< orphan*/ )) ; 

void wiiuse_handshake_expansion(struct wiimote_t *wm,ubyte *data,uword len)
{
	int id;
	ubyte val;
	ubyte *buf = NULL;

	switch(wm->expansion_state) {
		/* These two initialization writes disable the encryption */
		case 0:
			wm->expansion_state = 1;
			val = 0x55;
			wiiuse_write_data(wm,WM_EXP_MEM_ENABLE1,&val,1,wiiuse_handshake_expansion);
			break;
		case 1:
			wm->expansion_state = 2;
			val = 0x00;
			wiiuse_write_data(wm,WM_EXP_MEM_ENABLE2,&val,1,wiiuse_handshake_expansion);
			break;
		case 2:
			wm->expansion_state = 3;
			buf = __lwp_wkspace_allocate(sizeof(ubyte)*EXP_HANDSHAKE_LEN);
			wiiuse_read_data(wm,buf,WM_EXP_MEM_CALIBR,EXP_HANDSHAKE_LEN,wiiuse_handshake_expansion);
			break;
		case 3:
			if(!data || !len) return;
			id = BIG_ENDIAN_LONG(*(int*)(&data[220]));

			switch(id) {
				case EXP_ID_CODE_NUNCHUK:
					if(!nunchuk_handshake(wm,&wm->exp.nunchuk,data,len)) return;
					break;
				case EXP_ID_CODE_CLASSIC_CONTROLLER:
				case EXP_ID_CODE_CLASSIC_CONTROLLER_NYKOWING:
				case EXP_ID_CODE_CLASSIC_CONTROLLER_NYKOWING2:
				case EXP_ID_CODE_CLASSIC_CONTROLLER_NYKOWING3:
				case EXP_ID_CODE_CLASSIC_CONTROLLER_GENERIC:
				case EXP_ID_CODE_CLASSIC_CONTROLLER_GENERIC2:
				case EXP_ID_CODE_CLASSIC_CONTROLLER_GENERIC3:
				case EXP_ID_CODE_CLASSIC_CONTROLLER_GENERIC4:
				case EXP_ID_CODE_CLASSIC_CONTROLLER_GENERIC5:
				case EXP_ID_CODE_CLASSIC_WIIU_PRO:
					if(!classic_ctrl_handshake(wm,&wm->exp.classic,data,len)) return;
					break;
				default:
					if(!classic_ctrl_handshake(wm,&wm->exp.classic,data,len)) return;
					/*WIIMOTE_DISABLE_STATE(wm,WIIMOTE_STATE_EXP_HANDSHAKE);
					WIIMOTE_ENABLE_STATE(wm,WIIMOTE_STATE_EXP_FAILED);
					__lwp_wkspace_free(data);
					wiiuse_status(wm,NULL);
					return;*/
			}
			__lwp_wkspace_free(data);

			WIIMOTE_DISABLE_STATE(wm,WIIMOTE_STATE_EXP_HANDSHAKE);
			WIIMOTE_ENABLE_STATE(wm,WIIMOTE_STATE_EXP);
			wiiuse_set_ir_mode(wm);
			wiiuse_status(wm,NULL);
			break;
	}
}