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
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  VIDEOMODE_Update () ; 

__attribute__((used)) static int SetIntAndUpdateVideo(int *ptr, int value)
{
	int old_value = *ptr;
	if (old_value != value) {
		*ptr = value;
		if (!VIDEOMODE_Update()) {
			*ptr = old_value;
			return FALSE;
		}
	}
	return TRUE;
}