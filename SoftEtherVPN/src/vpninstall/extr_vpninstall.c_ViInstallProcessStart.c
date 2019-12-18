#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  instdir ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  hamcore ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  exe ;
typedef  int /*<<< orphan*/  arg ;
struct TYPE_10__ {int /*<<< orphan*/  CurrentInstalledPathW; int /*<<< orphan*/  VpnCMgrExeFileName; scalar_t__ CurrentInstalled; int /*<<< orphan*/  Build; } ;
typedef  TYPE_1__ VI_SETTING_ARCH ;
struct TYPE_11__ {int NoClose; int WindowsShutdowning; } ;
typedef  TYPE_2__ VI_INSTALL_DLG ;
struct TYPE_13__ {int DownloadNotRequired; int /*<<< orphan*/  DownloadedSettingPathW; scalar_t__ NormalMode; scalar_t__ WebMode; int /*<<< orphan*/ * DownloadedInstallerPathW; } ;
struct TYPE_12__ {int cbSize; char* lpVerb; char* lpParameters; int /*<<< orphan*/ * hProcess; int /*<<< orphan*/  nShow; int /*<<< orphan*/  fMask; int /*<<< orphan*/ * lpFile; } ;
typedef  TYPE_3__ SHELLEXECUTEINFOW ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConbinePath (char*,int,char*,char*) ; 
 int /*<<< orphan*/  ConbinePathW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DoEvents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Hide (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDCANCEL ; 
 scalar_t__ IDS_INSTALLSTART ; 
 scalar_t__ IDS_INSTALLSTART_ERROR ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MB_ICONSTOP ; 
 int MsIsServiceRunning (char*) ; 
 int /*<<< orphan*/ * MsRunAsUserExW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  MsStartService (char*) ; 
 int /*<<< orphan*/  MsgBox (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P_PROGRESS ; 
 int /*<<< orphan*/  SEE_MASK_NOCLOSEPROCESS ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  S_SIZEINFO ; 
 int /*<<< orphan*/  S_STATUS ; 
 int /*<<< orphan*/  SetPos (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ShellExecuteExW (TYPE_3__*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SwWaitForVpnClientPortReady (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,char*,...) ; 
 int UniIsEmptyStr (int /*<<< orphan*/ ) ; 
 int ViCheckExeSign (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ViGenerateVpnSMgrTempDirName (char*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* ViGetSuitableArchForCpu () ; 
 int /*<<< orphan*/  ViLoadCurrentInstalledStatusForArch (TYPE_1__*) ; 
 scalar_t__ WAIT_TIMEOUT ; 
 scalar_t__ WaitForSingleObject (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  _U (scalar_t__) ; 
 TYPE_4__ setting ; 
 scalar_t__ skip ; 
 int sleep_before_exit ; 

void ViInstallProcessStart(HWND hWnd, VI_INSTALL_DLG *d)
{
	wchar_t *exew;
	bool ok;
	char instdir[MAX_PATH];
	char hamcore[MAX_PATH];
	// Validate arguments
	if (hWnd == NULL || d == NULL)
	{
		return;
	}

	ViGenerateVpnSMgrTempDirName(instdir, sizeof(instdir), ViGetSuitableArchForCpu()->Build);
	ConbinePath(hamcore, sizeof(hamcore), instdir, "hamcore.se2");

	exew = setting.DownloadedInstallerPathW;
	d->NoClose = true;

	Hide(hWnd, IDCANCEL);
	SetPos(hWnd, P_PROGRESS, 100);
	Hide(hWnd, P_PROGRESS);
	Hide(hWnd, S_SIZEINFO);
	SetText(hWnd, S_STATUS, _U(IDS_INSTALLSTART+skip));

	ok = true;

	if (setting.DownloadNotRequired == false)
	{
		if (setting.WebMode && ViCheckExeSign(hWnd, exew) == false)
		{
			// The digital signature is not reliable
			ok = false;
		}
		else
		{
			// Installation
			HANDLE hProcess;
			SHELLEXECUTEINFOW info;

			// Run
			Zero(&info, sizeof(info));
			info.cbSize = sizeof(info);
			info.lpVerb = L"open";
			info.lpFile = exew;
			info.fMask = SEE_MASK_NOCLOSEPROCESS;
			info.lpParameters = L"/HIDESTARTCOMMAND:1 /DISABLEAUTOIMPORT:1 /ISWEBINSTALLER:1";
			info.nShow = SW_SHOWNORMAL;
			if (ShellExecuteExW(&info) == false)
			{
				MsgBox(hWnd, MB_ICONSTOP, _U(IDS_INSTALLSTART_ERROR+skip));
				ok = false;
			}
			else
			{
				hProcess = info.hProcess;

				// Wait for the install process to complete
				while (true)
				{
					if (WaitForSingleObject(hProcess, 50) != WAIT_TIMEOUT)
					{
						break;
					}

					DoEvents(hWnd);
				}
				CloseHandle(hProcess);
			}
		}
	}

	if (ok && d->WindowsShutdowning == false)
	{
		VI_SETTING_ARCH *a = ViGetSuitableArchForCpu();
		wchar_t arg[MAX_PATH];
		wchar_t exe[MAX_PATH];
		char *arg1 = "/easy";
		// Hide the screen
		Hide(hWnd, 0);

		if (setting.NormalMode)
		{
			arg1 = "/normal";
		}

		// (Just in case) start the VPN Client service
		if (MsIsServiceRunning("vpnclient") == false)
		{
			MsStartService("vpnclient");
		}

		// Wait for that the service becomes available
		SwWaitForVpnClientPortReady(0);

		if (UniIsEmptyStr(setting.DownloadedSettingPathW) == false)
		{
			// Start a connection by importing the configuration file into the VPN Client
			UniFormat(arg, sizeof(arg), L"%S \"%s\"", arg1, setting.DownloadedSettingPathW);
		}
		else
		{
			// Just start the Connection Manager
			UniFormat(arg, sizeof(arg), L"%S", arg1);
		}

		// Get the installation state
		ViLoadCurrentInstalledStatusForArch(a);

		if (a->CurrentInstalled)
		{
			HANDLE h;
			wchar_t filename[MAX_PATH];

			StrToUni(filename, sizeof(filename), a->VpnCMgrExeFileName);

			ConbinePathW(exe, sizeof(exe), a->CurrentInstalledPathW, filename);

			// Start the Connection Manager
			h = MsRunAsUserExW(exe, arg, false);
			if (h != NULL)
			{
				if (UniIsEmptyStr(setting.DownloadedSettingPathW) == false)
				{
					sleep_before_exit = true;
				}

				CloseHandle(h);
			}
		}
	}

	d->NoClose = false;
	Close(hWnd);
}