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
 int /*<<< orphan*/  CARD_ERROR_READY ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int* card_gamecode ; 
 int /*<<< orphan*/  memcpy (int*,char const*,int) ; 
 int strlen (char const*) ; 

s32 CARD_SetGamecode(const char *gamecode)
{
	u32 level,i;

	_CPU_ISR_Disable(level);
	for(i=0;i<4;i++) card_gamecode[i] = 0xff;
	if(gamecode && strlen(gamecode)<=4) memcpy(card_gamecode,gamecode,4) ;
	_CPU_ISR_Restore(level);

	return CARD_ERROR_READY;
}