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
typedef  scalar_t__ dt_version_t ;

/* Variables and functions */
 scalar_t__* _dtrace_versions ; 

int
dt_version_defined(dt_version_t v)
{
	int i;

	for (i = 0; _dtrace_versions[i] != 0; i++) {
		if (_dtrace_versions[i] == v)
			return (1);
	}

	return (0);
}