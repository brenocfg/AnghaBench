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
 int /*<<< orphan*/  fgInitialiseSpaceball () ; 
 int /*<<< orphan*/  fgWarning (char*) ; 
 int /*<<< orphan*/  sball_initialized ; 

int fgSpaceballNumButtons(void)
{
    if(!sball_initialized) {
        fgInitialiseSpaceball();
        if(!sball_initialized) {
            fgWarning("fgInitialiseSpaceball failed\n");
            return 0;
        }
    }

#if TARGET_HOST_POSIX_X11
    return 2;  /* TODO implement this properly */
#else
    return 0;
#endif
}