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
 int* card_company ; 
 int /*<<< orphan*/  memcpy (int*,char const*,int) ; 
 int strlen (char const*) ; 

s32 CARD_SetCompany(const char *company)
{
	u32 level,i;

	_CPU_ISR_Disable(level);
	for(i=0;i<2;i++) card_company[i] = 0xff;
	if(company && strlen(company)<=2) memcpy(card_company,company,2) ;
	_CPU_ISR_Restore(level);

	return CARD_ERROR_READY;
}