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
 int /*<<< orphan*/  FIPSPOST_TRACE_EVENT ; 

void cc_clear(size_t len, void *dst)
{
    FIPSPOST_TRACE_EVENT;
    volatile char *vptr = (volatile char *)dst;
    while (len--)
        *vptr++ = '\0';
}