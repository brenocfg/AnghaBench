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
typedef  int UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SetN ; 
 int CPU_regY ; 
 scalar_t__ Devices_GetAtariPath (size_t,char*) ; 
 size_t Devices_GetNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Devices_H_LoadProceed (int) ; 
 int /*<<< orphan*/ * Devices_atari_h_dir ; 
 char* Devices_h_exe_path ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IS_DIR_SEP (char const) ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int /*<<< orphan*/  Util_catpath (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* atari_filename ; 
 int /*<<< orphan*/  atari_path ; 
 int /*<<< orphan*/ * binf ; 
 scalar_t__ devbug ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int fread (int*,int,int,int /*<<< orphan*/ *) ; 
 size_t h_devnum ; 
 int /*<<< orphan*/  host_path ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static void Devices_H_Load(int mydos)
{
	const char *p;
	UBYTE buf[2];
	if (devbug)
		Log_print("LOAD Command");
	h_devnum = Devices_GetNumber(FALSE);
	if (h_devnum < 0)
		return;

	/* search for program on Devices_h_exe_path */
	for (p = Devices_h_exe_path; *p != '\0'; ) {
		int devnum;
		const char *q;
		char *r;
		if (p[0] == 'H' && p[1] >= '1' && p[1] <= '4' && p[2] == ':') {
			devnum = p[1] - '1';
			p += 3;
		}
		else
			devnum = h_devnum;
		for (q = p; *q != '\0' && *q != ';'; q++);
		r = atari_filename + (q - p);
		if (q != p) {
			memcpy(atari_filename, p, q - p);
			if (!IS_DIR_SEP(q[-1]))
				*r++ = '>';
		}
		if (Devices_GetAtariPath(devnum, r) == 0)
			return;
		Util_catpath(host_path, Devices_atari_h_dir[devnum], atari_path);
		binf = fopen(host_path, "rb");
		if (binf != NULL || *q == '\0')
			break;
		p = q + 1;
	}

	if (binf == NULL) {
		/* open from the specified location */
		if (Devices_GetAtariPath(h_devnum, atari_filename) == 0)
			return;
		Util_catpath(host_path, Devices_atari_h_dir[h_devnum], atari_path);
		binf = fopen(host_path, "rb");
		if (binf == NULL) {
			CPU_regY = 170;
			CPU_SetN;
			return;
		}
	}

	/* check header */
	if (fread(buf, 1, 2, binf) != 2 || buf[0] != 0xff || buf[1] != 0xff) {
		fclose(binf);
		binf = NULL;
		Log_print("H: load: not valid BIN file");
		CPU_regY = 180;
		CPU_SetN;
		return;
	}

	Devices_H_LoadProceed(mydos);
}