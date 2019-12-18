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
 scalar_t__ CompareResolutions (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolutions ; 
 unsigned int resolutions_size ; 

__attribute__((used)) static void RemoveDuplicateResolutions(void)
{
	unsigned int i, j;
	
	for (i = 0, j = 1; j < resolutions_size; ++j) {
		if (CompareResolutions(&resolutions[i], &resolutions[j]) != 0) {
			++i;
			if (i != j)
				resolutions[i] = resolutions[j];
		}
	}

	resolutions_size -= j - i - 1;
	/* Beware: unused end of RESOLUTIONS is still malloced! */
}