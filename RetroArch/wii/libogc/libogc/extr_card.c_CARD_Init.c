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
typedef  int u32 ;
typedef  int /*<<< orphan*/  s32 ;
typedef  int /*<<< orphan*/  card_block ;
struct TYPE_3__ {int /*<<< orphan*/  timeout_svc; int /*<<< orphan*/  wait_sync_queue; int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_ERROR_NOCARD ; 
 int /*<<< orphan*/  CARD_ERROR_READY ; 
 int /*<<< orphan*/  DSP_Init () ; 
 int /*<<< orphan*/  LWP_InitQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_CreateAlarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYS_RegisterResetFunc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int /*<<< orphan*/  card_company ; 
 int /*<<< orphan*/  card_gamecode ; 
 int card_inited ; 
 int /*<<< orphan*/  card_resetinfo ; 
 TYPE_1__* cardmap ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 

s32 CARD_Init(const char *gamecode,const char *company)
{
	u32 i,level;

	if(card_inited) return CARD_ERROR_READY;
	if(gamecode && strlen(gamecode)<=4) memcpy(card_gamecode,gamecode,4);
	if(company && strlen(company)<=2) memcpy(card_company,company,2);

	_CPU_ISR_Disable(level);
	DSP_Init();

	memset(cardmap,0,sizeof(card_block)*2);
	for(i=0;i<2;i++) {
		cardmap[i].result = CARD_ERROR_NOCARD;
		LWP_InitQueue(&cardmap[i].wait_sync_queue);
		SYS_CreateAlarm(&cardmap[i].timeout_svc);
	}
	SYS_RegisterResetFunc(&card_resetinfo);
	card_inited = 1;
	_CPU_ISR_Restore(level);
	return CARD_ERROR_READY;
}