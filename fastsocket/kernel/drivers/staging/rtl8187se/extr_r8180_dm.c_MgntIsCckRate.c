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
typedef  int u16 ;

/* Variables and functions */

bool
MgntIsCckRate(
        u16     rate
        )
{
        bool bReturn = false;

        if((rate <= 22) && (rate != 12) && (rate != 18))
        {
                bReturn = true;
        }

        return bReturn;
}