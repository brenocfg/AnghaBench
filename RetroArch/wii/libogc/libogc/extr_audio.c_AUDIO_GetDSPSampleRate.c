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
 size_t AI_CONTROL ; 
 int _SHIFTR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * _aiReg ; 

u32 AUDIO_GetDSPSampleRate()
{
	return (_SHIFTR(_aiReg[AI_CONTROL],6,1))^1;		//0^1(1) = 48Khz, 1^1(0) = 32Khz
}