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
typedef  size_t u8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DbgPrint (char*,...) ; 

u8_t zfFindFreqIndex(u8_t f, u8_t* fArray, u8_t fArraySize)
{
    u8_t i;
#ifdef ZM_ENABLE_TPC_WINDOWS_DEBUG
    DbgPrint("f=%d ", f);
    for (i=0; i<fArraySize; i++)
    {
        DbgPrint("%d ", fArray[i]);
    }
    DbgPrint("\n");
#endif
    i=fArraySize-2;
    while(1)
    {
        if (f >= fArray[i])
        {
            return i;
        }
        if (i!=0)
        {
            i--;
        }
        else
        {
            return 0;
        }
    }
}