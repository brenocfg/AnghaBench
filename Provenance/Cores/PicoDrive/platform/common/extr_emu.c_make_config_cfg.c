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
 int /*<<< orphan*/  PicoConfigFile ; 
 scalar_t__ config_slot ; 
 int /*<<< orphan*/  emu_make_path (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void make_config_cfg(char *cfg_buff_512)
{
	emu_make_path(cfg_buff_512, PicoConfigFile, 512-6);
	if (config_slot != 0)
	{
		char *p = strrchr(cfg_buff_512, '.');
		if (p == NULL)
			p = cfg_buff_512 + strlen(cfg_buff_512);
		sprintf(p, ".%i.cfg", config_slot);
	}
	cfg_buff_512[511] = 0;
}