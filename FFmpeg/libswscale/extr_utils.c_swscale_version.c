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
 int LIBSWSCALE_VERSION_INT ; 
 int LIBSWSCALE_VERSION_MICRO ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

unsigned swscale_version(void)
{
    av_assert0(LIBSWSCALE_VERSION_MICRO >= 100);
    return LIBSWSCALE_VERSION_INT;
}