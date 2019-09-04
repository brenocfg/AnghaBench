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
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static int convert_alignment(void *dest, const char *buf, int len)
{
    int a;
    if (sscanf(buf, "%d", &a) == 1) {
        /* convert V4 Style alignment to V4+ Style */
        *(int *)dest = a + ((a&4) >> 1) - 5*!!(a&8);
        return 1;
    }
    return 0;
}