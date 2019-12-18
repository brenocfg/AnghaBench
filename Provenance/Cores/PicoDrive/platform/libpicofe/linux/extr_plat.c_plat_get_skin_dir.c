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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int plat_get_data_dir (char*,int) ; 

int plat_get_skin_dir(char *dst, int len)
{
	int ret = plat_get_data_dir(dst, len);
	if (ret < 0)
		return ret;

	memcpy(dst + ret, "skin/", sizeof "skin/");
	return ret + sizeof("skin/") - 1;
}