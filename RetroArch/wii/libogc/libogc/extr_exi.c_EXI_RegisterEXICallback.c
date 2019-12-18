#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t s32 ;
struct TYPE_4__ {int /*<<< orphan*/ * CallbackEXI; } ;
typedef  TYPE_1__ exibus_priv ;
typedef  int /*<<< orphan*/ * EXICallback ;

/* Variables and functions */
 size_t EXI_CHANNEL_0 ; 
 size_t EXI_CHANNEL_2 ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __exi_setinterrupts (size_t,TYPE_1__*) ; 
 TYPE_1__* eximap ; 

EXICallback EXI_RegisterEXICallback(s32 nChn,EXICallback exi_cb)
{
	u32 level;
	EXICallback old = NULL;
	exibus_priv *exi = &eximap[nChn];
	_CPU_ISR_Disable(level);
	old = exi->CallbackEXI;
	exi->CallbackEXI = exi_cb;
	if(nChn==EXI_CHANNEL_2) __exi_setinterrupts(EXI_CHANNEL_0,&eximap[EXI_CHANNEL_0]);
	else __exi_setinterrupts(nChn,exi);
	_CPU_ISR_Restore(level);
	return old;
}