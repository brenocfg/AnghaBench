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
 int DLM_LVB_LEN ; 

__attribute__((used)) static inline int dlm_lvb_is_empty(char *lvb)
{
	int i;
	for (i=0; i<DLM_LVB_LEN; i++)
		if (lvb[i])
			return 0;
	return 1;
}