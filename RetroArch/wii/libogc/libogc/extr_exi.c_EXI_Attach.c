#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t s32 ;
struct TYPE_3__ {scalar_t__ exi_idtime; } ;
typedef  TYPE_1__ exibus_priv ;
typedef  int /*<<< orphan*/  EXICallback ;

/* Variables and functions */
 int /*<<< orphan*/  EXI_Probe (size_t) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 size_t __exi_attach (size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* eximap ; 

s32 EXI_Attach(s32 nChn,EXICallback ext_cb)
{
	s32 ret;
	u32 level;
	exibus_priv *exi = &eximap[nChn];
	EXI_Probe(nChn);

	_CPU_ISR_Disable(level);
	if(exi->exi_idtime) {
		ret = __exi_attach(nChn,ext_cb);
	} else
		ret = 0;
	_CPU_ISR_Restore(level);
	return ret;
}