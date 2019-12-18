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
 int /*<<< orphan*/  ARR_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  group_name_maps ; 
 char const* id2name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

const char *M68K_group_name(csh handle, unsigned int id)
{
#ifndef CAPSTONE_DIET
	return id2name(group_name_maps, ARR_SIZE(group_name_maps), id);
#else
	return NULL;
#endif
}