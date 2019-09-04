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
typedef  int /*<<< orphan*/  I_32 ;
typedef  scalar_t__ IDATA ;

/* Variables and functions */
 scalar_t__ FD_BIAS ; 
 int /*<<< orphan*/  close (int) ; 

I_32 hyfile_close (IDATA fd)
{
    
#if (FD_BIAS != 0)
    if (fd < FD_BIAS) {
        /* Cannot close STD streams, and no other FD's should exist <FD_BIAS */
	    return -1;
    }
#endif
    
    return close ((int) (fd - FD_BIAS));
}