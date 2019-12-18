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
 int /*<<< orphan*/  PICO_HOME_DIR ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  mkdir (char*,int) ; 
 int plat_get_data_dir (char*,int) ; 
 int snprintf (char*,int,char*,char const*,int /*<<< orphan*/ ) ; 

int plat_get_root_dir(char *dst, int len)
{
#if !defined(__GP2X__) && !defined(PANDORA)
	const char *home = getenv("HOME");
	int ret;

	if (home != NULL) {
		ret = snprintf(dst, len, "%s%s", home, PICO_HOME_DIR);
		if (ret >= len)
			ret = len - 1;
		mkdir(dst, 0755);
		return ret;
	}
#endif
	return plat_get_data_dir(dst, len);
}