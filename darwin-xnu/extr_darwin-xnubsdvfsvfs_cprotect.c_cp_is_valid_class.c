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
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ PROTECTION_CLASS_A ; 
 scalar_t__ PROTECTION_CLASS_D ; 
 scalar_t__ PROTECTION_CLASS_DIR_NONE ; 
 scalar_t__ PROTECTION_CLASS_F ; 

int
cp_is_valid_class(int isdir, int32_t protectionclass)
{
	/*
	 * The valid protection classes are from 0 -> N
	 * We use a signed argument to detect unassigned values from
	 * directory entry creation time in HFS.
	 */
	if (isdir) {
		/* Directories are not allowed to have F, but they can have "NONE" */
		return ((protectionclass >= PROTECTION_CLASS_DIR_NONE) &&
				(protectionclass <= PROTECTION_CLASS_D));
	}
	else {
		return ((protectionclass >= PROTECTION_CLASS_A) &&
				(protectionclass <= PROTECTION_CLASS_F));
	}
}