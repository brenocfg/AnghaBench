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

void VpnCmdInitBootPath()
{
#ifdef	OS_WIN32
	char exe_path[MAX_PATH];
	char tmp[MAX_PATH];
	GetExeName(exe_path, sizeof(exe_path));

	if (SearchStrEx(exe_path, "ham.exe", 0, false) != INFINITE || SearchStrEx(exe_path, "ham_x64.exe", 0, false) != INFINITE || SearchStrEx(exe_path, "ham_ia64.exe", 0, false) != INFINITE)
	{
		return;
	}

	if (MsIsAdmin())
	{
		UINT current_ver;

		// Get the version of vpncmd that is currently installed
		current_ver = MsRegReadInt(REG_LOCAL_MACHINE, VPNCMD_BOOTSTRAP_REG_KEYNAME, VPNCMD_BOOTSTRAP_REG_VALUENAME_VER);

		if ((CEDAR_VERSION_BUILD >= current_ver) ||
			MsRegIsValue(REG_LOCAL_MACHINE, VPNCMD_BOOTSTRAP_REG_KEYNAME, VPNCMD_BOOTSTRAP_REG_VALUENAME_PATH) == false)
		{
			char *src_filename;
			bool b = false;
			// Copy the vpncmdsys.exe to system32
			if (MsIsNt())
			{
				Format(tmp, sizeof(tmp), "%s\\vpncmd.exe", MsGetSystem32Dir());
			}
			else
			{
				Format(tmp, sizeof(tmp), "%s\\vpncmd.exe", MsGetWindowsDir());
			}

			src_filename = VPNCMD_BOOTSTRAP_FILENAME;

			if (IsX64())
			{
				src_filename = VPNCMD_BOOTSTRAP_FILENAME_X64;
			}

			if (IsIA64())
			{
				src_filename = VPNCMD_BOOTSTRAP_FILENAME_IA64;
			}

			b = true;

			if (MsIs64BitWindows() == false || Is64())
			{
				if (IsFile(tmp) == false || (CEDAR_VERSION_BUILD > current_ver) || MsRegIsValue(REG_LOCAL_MACHINE, VPNCMD_BOOTSTRAP_REG_KEYNAME, VPNCMD_BOOTSTRAP_REG_VALUENAME_PATH) == false)
				{
					b = FileCopy(src_filename, tmp);
				}
			}
			else
			{
				void *wow;

				wow = MsDisableWow64FileSystemRedirection();

				if (true)
				{
					if (IsFile(tmp) == false || (CEDAR_VERSION_BUILD > current_ver) || MsRegIsValue(REG_LOCAL_MACHINE, VPNCMD_BOOTSTRAP_REG_KEYNAME, VPNCMD_BOOTSTRAP_REG_VALUENAME_PATH) == false)
					{
						b = FileCopy(src_filename, tmp);
					}
				}

				MsRestoreWow64FileSystemRedirection(wow);

				if (true)
				{
					if (IsFile(tmp) == false || (CEDAR_VERSION_BUILD > current_ver) || MsRegIsValue(REG_LOCAL_MACHINE, VPNCMD_BOOTSTRAP_REG_KEYNAME, VPNCMD_BOOTSTRAP_REG_VALUENAME_PATH) == false)
					{
						b = FileCopy(src_filename, tmp);
					}
				}
			}

			// Because the currently running prompt is newer version, overwrite the registry
			if (MsIs64BitWindows() == false)
			{
				MsRegWriteStr(REG_LOCAL_MACHINE, VPNCMD_BOOTSTRAP_REG_KEYNAME, VPNCMD_BOOTSTRAP_REG_VALUENAME_PATH, exe_path);
				MsRegWriteInt(REG_LOCAL_MACHINE, VPNCMD_BOOTSTRAP_REG_KEYNAME, VPNCMD_BOOTSTRAP_REG_VALUENAME_VER, CEDAR_VERSION_BUILD);
			}
			else
			{
				MsRegWriteStrEx2(REG_LOCAL_MACHINE, VPNCMD_BOOTSTRAP_REG_KEYNAME, VPNCMD_BOOTSTRAP_REG_VALUENAME_PATH, exe_path, true, false);
				MsRegWriteIntEx2(REG_LOCAL_MACHINE, VPNCMD_BOOTSTRAP_REG_KEYNAME, VPNCMD_BOOTSTRAP_REG_VALUENAME_VER, CEDAR_VERSION_BUILD, true, false);

				MsRegWriteStrEx2(REG_LOCAL_MACHINE, VPNCMD_BOOTSTRAP_REG_KEYNAME, VPNCMD_BOOTSTRAP_REG_VALUENAME_PATH, exe_path, false, true);
				MsRegWriteIntEx2(REG_LOCAL_MACHINE, VPNCMD_BOOTSTRAP_REG_KEYNAME, VPNCMD_BOOTSTRAP_REG_VALUENAME_VER, CEDAR_VERSION_BUILD, false, true);
			}
		}
	}
#endif	// OS_WIN32
}