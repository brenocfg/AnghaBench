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
typedef  int u32 ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int PAD_ENABLEDMASK (int /*<<< orphan*/ ) ; 
 int PAD_MOTOR_STOP_HARD ; 
 int SI_GC_NOMOTOR ; 
 int SI_GetType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SI_SetCommand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SI_TransferCommands () ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int __pad_analogmode ; 
 int __pad_enabledbits ; 
 int __pad_spec ; 

void PAD_ControlMotor(s32 chan,u32 cmd)
{
	u32 level;
	u32 mask,type;

	_CPU_ISR_Disable(level);

	mask = PAD_ENABLEDMASK(chan);
	if(__pad_enabledbits&mask) {
		type = SI_GetType(chan);
		if(!(type&SI_GC_NOMOTOR)) {
			if(__pad_spec<2 && cmd==PAD_MOTOR_STOP_HARD) cmd = 0;

			cmd = 0x00400000|__pad_analogmode|(cmd&0x03);
			SI_SetCommand(chan,cmd);
			SI_TransferCommands();
		}
	}
	_CPU_ISR_Restore(level);
}