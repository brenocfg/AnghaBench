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
typedef  int /*<<< orphan*/  u8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void zfPrintTp(u8_t* pwr0, u8_t* vpd0, u8_t* pwr1, u8_t* vpd1)
{
    #ifdef ZM_ENABLE_TPC_WINDOWS_DEBUG
    DbgPrint("pwr0 : %d, %d, %d, %d ,%d\n", pwr0[0], pwr0[1], pwr0[2], pwr0[3], pwr0[4]);
    DbgPrint("vpd0 : %d, %d, %d, %d ,%d\n", vpd0[0], vpd0[1], vpd0[2], vpd0[3], vpd0[4]);
    DbgPrint("pwr1 : %d, %d, %d, %d ,%d\n", pwr1[0], pwr1[1], pwr1[2], pwr1[3], pwr1[4]);
    DbgPrint("vpd1 : %d, %d, %d, %d ,%d\n", vpd1[0], vpd1[1], vpd1[2], vpd1[3], vpd1[4]);
    #endif
}