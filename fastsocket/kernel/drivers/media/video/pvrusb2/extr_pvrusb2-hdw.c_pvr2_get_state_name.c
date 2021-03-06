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
 unsigned int ARRAY_SIZE (char const**) ; 
 char const** pvr2_state_names ; 

__attribute__((used)) static const char *pvr2_get_state_name(unsigned int st)
{
	if (st < ARRAY_SIZE(pvr2_state_names)) {
		return pvr2_state_names[st];
	}
	return "???";
}