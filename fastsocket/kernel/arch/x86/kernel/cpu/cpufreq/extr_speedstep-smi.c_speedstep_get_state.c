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

/* Variables and functions */
 int GET_SPEEDSTEP_STATE ; 
 int /*<<< orphan*/  dprintk (char*,int,int) ; 
 int smi_cmd ; 
 int smi_port ; 
 int smi_sig ; 

__attribute__((used)) static int speedstep_get_state(void)
{
	u32 function = GET_SPEEDSTEP_STATE;
	u32 result, state, edi, command, dummy;

	command = (smi_sig & 0xffffff00) | (smi_cmd & 0xff);

	dprintk("trying to determine current setting with command %x "
		"at port %x\n", command, smi_port);

	__asm__ __volatile__(
		"push %%ebp\n"
		"out %%al, (%%dx)\n"
		"pop %%ebp\n"
		: "=a" (result),
		  "=b" (state), "=D" (edi),
		  "=c" (dummy), "=d" (dummy), "=S" (dummy)
		: "a" (command), "b" (function), "c" (0),
		  "d" (smi_port), "S" (0), "D" (0)
	);

	dprintk("state is %x, result is %x\n", state, result);

	return state & 1;
}