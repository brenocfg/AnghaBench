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
typedef  int /*<<< orphan*/  csh ;

/* Variables and functions */
 unsigned int ARR_SIZE (char const**) ; 
 char const** GroupNames ; 

const char *MOS65XX_group_name(csh handle, unsigned int id)
{
#ifdef CAPSTONE_DIET
	return NULL;
#else
	if (id >= ARR_SIZE(GroupNames)) {
		return NULL;
	}
	return GroupNames[(int)id];
#endif
}