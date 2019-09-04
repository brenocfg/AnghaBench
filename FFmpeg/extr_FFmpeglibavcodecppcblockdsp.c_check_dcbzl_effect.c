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

/* Variables and functions */

__attribute__((used)) static long check_dcbzl_effect(void)
{
    long count = 0;
#if HAVE_DCBZL
    register char *fakedata = av_malloc(1024);
    register char *fakedata_middle;
    register long zero = 0, i = 0;

    if (!fakedata)
        return 0L;

    fakedata_middle = fakedata + 512;

    memset(fakedata, 0xFF, 1024);

    /* Below the constraint "b" seems to mean "address base register"
     * in gcc-3.3 / RS/6000 speaks. Seems to avoid using r0, so.... */
    __asm__ volatile ("dcbzl %0, %1" :: "b" (fakedata_middle), "r" (zero));

    for (i = 0; i < 1024; i++)
        if (fakedata[i] == (char) 0)
            count++;

    av_free(fakedata);
#endif

    return count;
}