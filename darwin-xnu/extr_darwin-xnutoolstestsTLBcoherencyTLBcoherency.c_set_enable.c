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
 int CTL_KERN ; 
 int KERN_KDEBUG ; 
 int KERN_KDENABLE ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ sysctl (int*,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void set_enable(int val)
{
	int mib[6];
	size_t needed;

        mib[0] = CTL_KERN;
        mib[1] = KERN_KDEBUG;
        mib[2] = KERN_KDENABLE;
        mib[3] = val;
        mib[4] = 0;
        mib[5] = 0;

        if (sysctl(mib, 4, NULL, &needed, NULL, 0) < 0) {
                printf("trace facility failure, KERN_KDENABLE\n");
	}
}