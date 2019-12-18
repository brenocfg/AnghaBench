#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int button; void* err; } ;
typedef  TYPE_1__ PADStatus ;

/* Variables and functions */
 int PAD_ENABLEDMASK (int) ; 
 void* PAD_ERR_NONE ; 
 void* PAD_ERR_NOT_READY ; 
 void* PAD_ERR_NO_CONTROLLER ; 
 void* PAD_ERR_TRANSFER ; 
 int /*<<< orphan*/  PAD_Reset (int /*<<< orphan*/ ) ; 
 int SI_ERROR_NO_RESPONSE ; 
 int /*<<< orphan*/  SI_GetResponse (int,int*) ; 
 int SI_GetStatus (int) ; 
 int SI_GetType (int) ; 
 int /*<<< orphan*/  SI_GetTypeAsync (int,int /*<<< orphan*/ ) ; 
 scalar_t__ SI_IsChanBusy (int) ; 
 int /*<<< orphan*/  SI_Transfer (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SI_WIRELESS_STATE ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int __pad_checkingbits ; 
 int /*<<< orphan*/  __pad_cmdreadorigin ; 
 int /*<<< orphan*/  __pad_disable (int) ; 
 int __pad_enabledbits ; 
 int /*<<< orphan*/  __pad_makestatus (int,int*,TYPE_1__*) ; 
 int /*<<< orphan*/ * __pad_origin ; 
 int /*<<< orphan*/  __pad_originupdatecallback ; 
 int __pad_pendingbits ; 
 int /*<<< orphan*/  __pad_receivecheckcallback ; 
 int __pad_resettingbits ; 
 int __pad_resettingchan ; 
 int __pad_waitingbits ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

u32 PAD_Read(PADStatus *status)
{
	u32 chan,mask,ret;
	u32 level,sistatus,type;
	u32 buf[2];
	_CPU_ISR_Disable(level);
	chan = 0;
	ret = 0;
	while(chan<4) {
		mask = PAD_ENABLEDMASK(chan);
		if(__pad_pendingbits&mask) {
			PAD_Reset(0);
			memset(&status[chan],0,sizeof(PADStatus));
			status[chan].err = PAD_ERR_NOT_READY;
		} else if(__pad_resettingbits&mask || __pad_resettingchan==chan) {
			memset(&status[chan],0,sizeof(PADStatus));
			status[chan].err = PAD_ERR_NOT_READY;
		} else if(!(__pad_enabledbits&mask)) {
			memset(&status[chan],0,sizeof(PADStatus));
			status[chan].err = PAD_ERR_NO_CONTROLLER;
		} else {
			if(SI_IsChanBusy(chan)) {
				memset(&status[chan],0,sizeof(PADStatus));
				status[chan].err = PAD_ERR_TRANSFER;
			} else {
				sistatus = SI_GetStatus(chan);
				if(sistatus&SI_ERROR_NO_RESPONSE) {
					SI_GetResponse(chan,(void*)buf);
					if(!(__pad_waitingbits&mask)) {
						memset(&status[chan],0,sizeof(PADStatus));
						status[chan].err = PAD_ERR_NONE;
						if(!(__pad_checkingbits&mask)) {
							__pad_checkingbits |= mask;
							SI_GetTypeAsync(chan,__pad_receivecheckcallback);
						}
					} else {
						__pad_disable(chan);
						memset(&status[chan],0,sizeof(PADStatus));
						status[chan].err = PAD_ERR_NO_CONTROLLER;
					}
				} else {
					type = SI_GetType(chan);
					if(!(type&SI_WIRELESS_STATE)) ret |= mask;
					if(!SI_GetResponse(chan,buf)
						|| buf[0]&0x80000000) {
						memset(&status[chan],0,sizeof(PADStatus));
						status[chan].err = PAD_ERR_TRANSFER;
					} else {
						__pad_makestatus(chan,buf,&status[chan]);
						if(status[chan].button&0x00002000) {
							memset(&status[chan],0,sizeof(PADStatus));
							status[chan].err = PAD_ERR_TRANSFER;
							SI_Transfer(chan,&__pad_cmdreadorigin,1,__pad_origin[chan],10,__pad_originupdatecallback,0);
						} else {
							status[chan].err = PAD_ERR_NONE;
							status[chan].button &= ~0x80;
						}
					}
				}
			}
		}
		chan++;

	}
	_CPU_ISR_Restore(level);

	return ret;
}