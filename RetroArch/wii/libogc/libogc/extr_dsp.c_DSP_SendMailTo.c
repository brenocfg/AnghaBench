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
 int _SHIFTR (int,int,int) ; 
 int* _dspReg ; 

void DSP_SendMailTo(u32 mail)
{
	_dspReg[0] = _SHIFTR(mail,16,16);
	_dspReg[1] = (mail&0xffff);
}