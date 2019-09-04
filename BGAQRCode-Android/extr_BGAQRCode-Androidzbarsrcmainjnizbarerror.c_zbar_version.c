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
 unsigned int ZBAR_VERSION_MAJOR ; 
 unsigned int ZBAR_VERSION_MINOR ; 

int zbar_version (unsigned *major,
                  unsigned *minor)
{
    if(major)
        *major = ZBAR_VERSION_MAJOR;
    if(minor)
        *minor = ZBAR_VERSION_MINOR;
    return(0);
}