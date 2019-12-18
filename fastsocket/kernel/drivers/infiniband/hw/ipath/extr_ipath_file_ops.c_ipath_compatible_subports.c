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
 int IPATH_USER_SWMAJOR ; 
 int IPATH_USER_SWMINOR ; 

__attribute__((used)) static int ipath_compatible_subports(int user_swmajor, int user_swminor)
{
	/* this code is written long-hand for clarity */
	if (IPATH_USER_SWMAJOR != user_swmajor) {
		/* no promise of compatibility if major mismatch */
		return 0;
	}
	if (IPATH_USER_SWMAJOR == 1) {
		switch (IPATH_USER_SWMINOR) {
		case 0:
		case 1:
		case 2:
			/* no subport implementation so cannot be compatible */
			return 0;
		case 3:
			/* 3 is only compatible with itself */
			return user_swminor == 3;
		default:
			/* >= 4 are compatible (or are expected to be) */
			return user_swminor >= 4;
		}
	}
	/* make no promises yet for future major versions */
	return 0;
}