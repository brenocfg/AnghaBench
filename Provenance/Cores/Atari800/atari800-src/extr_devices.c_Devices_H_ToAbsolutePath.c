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
typedef  int /*<<< orphan*/  UWORD ;
typedef  int UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ClrN ; 
 int /*<<< orphan*/  CPU_SetN ; 
 int CPU_regY ; 
 scalar_t__ Devices_GetHostPath (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Devices_ICBLLZ ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Log_print (char*) ; 
 int /*<<< orphan*/  MEMORY_PutByte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MEMORY_dGetWordAligned (int /*<<< orphan*/ ) ; 
 char const Util_DIR_SEP_CHAR ; 
 int /*<<< orphan*/  Util_direxists (int /*<<< orphan*/ ) ; 
 char* atari_path ; 
 scalar_t__ devbug ; 
 int /*<<< orphan*/  host_path ; 

__attribute__((used)) static void Devices_H_ToAbsolutePath(void)
{
	UWORD bufadr;
	const char *p;

	if (devbug)
		Log_print("To Absolute Path Command");

	if (Devices_GetHostPath(FALSE) == 0)
		return;

	/* XXX: we sometimes check here for directories
	   with a trailing Util_DIR_SEP_CHAR. It seems to work on Win32 and DJGPP. */
	if (!Util_direxists(host_path)) {
		CPU_regY = 150;
		CPU_SetN;
		return;
	}

	bufadr = MEMORY_dGetWordAligned(Devices_ICBLLZ);
	if (atari_path[0] != '\0') {
		MEMORY_PutByte(bufadr, '>');
		bufadr++;
		for (p = atari_path; *p != '\0'; p++) {
			if (*p == Util_DIR_SEP_CHAR) {
				if (p[1] == '\0')
					break;
				MEMORY_PutByte(bufadr, '>');
			}
			else
				MEMORY_PutByte(bufadr, (UBYTE) *p);
			bufadr++;
		}
	}
	MEMORY_PutByte(bufadr, 0x00);

	CPU_regY = 1;
	CPU_ClrN;
}