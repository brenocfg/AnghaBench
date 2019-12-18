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
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PicoInit () ; 
 int /*<<< orphan*/  PicoMCDcloseTray ; 
 int /*<<< orphan*/  PicoMCDopenTray ; 
 int /*<<< orphan*/  PicoMessage ; 
 int /*<<< orphan*/  config_readlrom (char*) ; 
 int /*<<< orphan*/  emu_tray_close ; 
 int /*<<< orphan*/  emu_tray_open ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_config_cfg (char*) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  mkdir_path (char*,int,char*) ; 
 int /*<<< orphan*/  p32x_bios_m ; 
 int /*<<< orphan*/  p32x_bios_s ; 
 int plat_get_root_dir (char*,int) ; 
 int /*<<< orphan*/  plat_status_msg_busy_next ; 
 int /*<<< orphan*/  pprof_init () ; 
 int /*<<< orphan*/  sndout_init () ; 

void emu_init(void)
{
	char path[512];
	int pos;

#if 0
	// FIXME: handle through menu, etc
	FILE *f;
	f = fopen("32X_M_BIOS.BIN", "rb");
	p32x_bios_m = malloc(2048);
	fread(p32x_bios_m, 1, 2048, f);
	fclose(f);
	f = fopen("32X_S_BIOS.BIN", "rb");
	p32x_bios_s = malloc(1024);
	fread(p32x_bios_s, 1, 1024, f);
	fclose(f);
#endif

	/* make dirs for saves */
	pos = plat_get_root_dir(path, sizeof(path) - 4);
	mkdir_path(path, pos, "mds");
	mkdir_path(path, pos, "srm");
	mkdir_path(path, pos, "brm");
	mkdir_path(path, pos, "cfg");

	pprof_init();

	make_config_cfg(path);
	config_readlrom(path);

	PicoInit();
	PicoMessage = plat_status_msg_busy_next;
	PicoMCDopenTray = emu_tray_open;
	PicoMCDcloseTray = emu_tray_close;

	sndout_init();
}