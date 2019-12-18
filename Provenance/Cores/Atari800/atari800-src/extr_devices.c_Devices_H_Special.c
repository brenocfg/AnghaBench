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
 int /*<<< orphan*/  CPU_SetN ; 
 int CPU_regY ; 
 int /*<<< orphan*/  Devices_H_ChangeDirectory () ; 
 int /*<<< orphan*/  Devices_H_Delete () ; 
 int /*<<< orphan*/  Devices_H_DiskInfo () ; 
 int /*<<< orphan*/  Devices_H_FileLength () ; 
 int /*<<< orphan*/  Devices_H_Load (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Devices_H_Lock () ; 
 int /*<<< orphan*/  Devices_H_MakeDirectory () ; 
 int /*<<< orphan*/  Devices_H_Note () ; 
 int /*<<< orphan*/  Devices_H_Point () ; 
 int /*<<< orphan*/  Devices_H_RemoveDirectory () ; 
 int /*<<< orphan*/  Devices_H_Rename () ; 
 int /*<<< orphan*/  Devices_H_ToAbsolutePath () ; 
 int /*<<< orphan*/  Devices_H_Unlock () ; 
 int /*<<< orphan*/  Devices_ICCOMZ ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  Log_print (char*,...) ; 
 int MEMORY_dGetByte (int /*<<< orphan*/ ) ; 
 scalar_t__ devbug ; 

__attribute__((used)) static void Devices_H_Special(void)
{
	if (devbug)
		Log_print("HHSPEC");

	switch (MEMORY_dGetByte(Devices_ICCOMZ)) {
#ifdef DO_RENAME
	case 0x20:
		Devices_H_Rename();
		return;
#endif
#ifdef HAVE_UTIL_UNLINK
	case 0x21:
		Devices_H_Delete();
		return;
#endif
#ifdef DO_LOCK
	case 0x23:
		Devices_H_Lock();
		return;
	case 0x24:
		Devices_H_Unlock();
		return;
#endif
	case 0x26:
		Devices_H_Note();
		return;
	case 0x25:
		Devices_H_Point();
		return;
	case 0x27: /* Sparta, MyDOS=Load */
		Devices_H_FileLength();
		return;
	case 0x28: /* Sparta */
		Devices_H_Load(FALSE);
		return;
#ifdef DO_MKDIR
	case 0x22: /* MyDOS */
	case 0x2a: /* MyDOS, Sparta */
		Devices_H_MakeDirectory();
		return;
#endif
#ifdef DO_RMDIR
	case 0x2b: /* Sparta */
		Devices_H_RemoveDirectory();
		return;
#endif
	case 0x29: /* MyDOS */
	case 0x2c: /* Sparta */
		Devices_H_ChangeDirectory();
		return;
	case 0x2f: /* Sparta */
		Devices_H_DiskInfo();
		return;
	case 0x30: /* Sparta */
		Devices_H_ToAbsolutePath();
		return;
	case 0xfe:
		if (devbug)
			Log_print("FORMAT Command");
		break;
	default:
		if (devbug)
			Log_print("UNKNOWN Command %02X", MEMORY_dGetByte(Devices_ICCOMZ));
		break;
	}

	CPU_regY = 168; /* invalid device command */
	CPU_SetN;
}