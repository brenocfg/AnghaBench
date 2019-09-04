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
 int OSRun (char*,char*,int,int) ; 

bool Run(char *filename, char *arg, bool hide, bool wait)
{
	// Validate arguments
	if (filename == NULL)
	{
		return false;
	}

	return OSRun(filename, arg, hide, wait);
}