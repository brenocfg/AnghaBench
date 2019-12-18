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
 int GetModuleFileName (int /*<<< orphan*/ *,char*,int) ; 

int plat_get_root_dir(char *dst, int len)
{
	int ml;

	ml = GetModuleFileName(NULL, dst, len);
	while (ml > 0 && dst[ml] != '\\')
		ml--;
	if (ml != 0)
		ml++;

	dst[ml] = 0;
	return ml;
}