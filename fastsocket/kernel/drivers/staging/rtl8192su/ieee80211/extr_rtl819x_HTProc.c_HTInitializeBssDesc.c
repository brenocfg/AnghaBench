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
struct TYPE_3__ {int bdSupportHT; int bdRT2RTAggregation; int bdRT2RTLongSlotTime; scalar_t__ RT2RT_HT_Mode; int /*<<< orphan*/  bdHTSpecVer; scalar_t__ bdHTInfoLen; int /*<<< orphan*/  bdHTInfoBuf; scalar_t__ bdHTCapLen; int /*<<< orphan*/  bdHTCapBuf; } ;
typedef  scalar_t__ RT_HT_CAPBILITY ;
typedef  TYPE_1__* PBSS_HT ;

/* Variables and functions */
 int /*<<< orphan*/  HT_SPEC_VER_IEEE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void HTInitializeBssDesc(PBSS_HT pBssHT)
{

	pBssHT->bdSupportHT = false;
	memset(pBssHT->bdHTCapBuf, 0, sizeof(pBssHT->bdHTCapBuf));
	pBssHT->bdHTCapLen = 0;
	memset(pBssHT->bdHTInfoBuf, 0, sizeof(pBssHT->bdHTInfoBuf));
	pBssHT->bdHTInfoLen = 0;

	pBssHT->bdHTSpecVer= HT_SPEC_VER_IEEE;

	pBssHT->bdRT2RTAggregation = false;
	pBssHT->bdRT2RTLongSlotTime = false;
	pBssHT->RT2RT_HT_Mode = (RT_HT_CAPBILITY)0;
}