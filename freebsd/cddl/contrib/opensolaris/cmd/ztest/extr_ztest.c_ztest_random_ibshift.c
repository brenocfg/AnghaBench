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
 int DN_MAX_INDBLKSHIFT ; 
 int DN_MIN_INDBLKSHIFT ; 
 int ztest_random (int) ; 

__attribute__((used)) static int
ztest_random_ibshift(void)
{
	return (DN_MIN_INDBLKSHIFT +
	    ztest_random(DN_MAX_INDBLKSHIFT - DN_MIN_INDBLKSHIFT + 1));
}