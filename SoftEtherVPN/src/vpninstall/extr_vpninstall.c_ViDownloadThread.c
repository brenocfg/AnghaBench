#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  files ;
typedef  int /*<<< orphan*/  filename_w ;
struct TYPE_8__ {int /*<<< orphan*/  Path; } ;
typedef  TYPE_1__ VI_SETTING_ARCH ;
struct TYPE_9__ {int /*<<< orphan*/  Buf; int /*<<< orphan*/  BufSize; scalar_t__ Halt; int /*<<< orphan*/  hWnd; } ;
typedef  TYPE_2__ VI_INSTALL_DLG ;
typedef  int /*<<< orphan*/  VI_FILE ;
struct TYPE_10__ {float FileName; float DestPathW; int /*<<< orphan*/  SrcPath; } ;
typedef  TYPE_3__ VI_DOWNLOAD_FILE ;
typedef  size_t UINT ;
struct TYPE_11__ {int /*<<< orphan*/  DownloadedSettingPathW; int /*<<< orphan*/  DownloadedInstallerPathW; scalar_t__ DownloadNotRequired; int /*<<< orphan*/  SettingPath; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  int /*<<< orphan*/  IO ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ConbinePathW (float,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileCreateW (float) ; 
 int /*<<< orphan*/  FileWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  GetFileNameFromFilePath (float,int,int /*<<< orphan*/ ) ; 
 scalar_t__ IDS_DOWNLOADING ; 
 scalar_t__ IDS_DOWNLOADING2 ; 
 scalar_t__ IDS_DOWNLOADING3 ; 
 scalar_t__ IDS_DOWNLOADSTART ; 
 scalar_t__ IDS_DOWNLOAD_ERROR ; 
 scalar_t__ IDS_TEMP_ERROR ; 
 size_t INFINITE ; 
 int IsEmptyStr (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MB_ICONSTOP ; 
 int /*<<< orphan*/  MakeSafeFileName (float,int,float) ; 
 int /*<<< orphan*/  MsGetMyTempDirW () ; 
 int /*<<< orphan*/  MsgBoxEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  PostMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ S_SIZEINFO ; 
 scalar_t__ S_STATUS ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,float) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,float,...) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,float) ; 
 int /*<<< orphan*/  ViCloseFile (int /*<<< orphan*/ *) ; 
 size_t ViGetFileSize (int /*<<< orphan*/ *) ; 
 TYPE_1__* ViGetSuitableArchForCpu () ; 
 int /*<<< orphan*/  ViInstallDlgCancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ViInstallDlgSetPos (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ViInstallDlgSetText (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ViOpenFile (int /*<<< orphan*/ ) ; 
 size_t ViReadFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WM_VI_DOWNLOAD_FINISHED ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  _U (scalar_t__) ; 
 TYPE_4__ setting ; 
 scalar_t__ skip ; 

void ViDownloadThread(THREAD *thread, void *param)
{
	VI_INSTALL_DLG *d;
	VI_SETTING_ARCH *a;
	HWND hWnd;
	UINT num_files = 2;
	VI_DOWNLOAD_FILE files[2];
	VI_DOWNLOAD_FILE *f;
	UINT i;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	d = (VI_INSTALL_DLG *)param;
	hWnd = d->hWnd;

	Zero(files, sizeof(files));

	a = ViGetSuitableArchForCpu();

	// File body
	f = &files[0];
	StrCpy(f->SrcPath, sizeof(f->SrcPath), a->Path);

	// Configuration file
	if (IsEmptyStr(setting.SettingPath) == false)
	{
		f = &files[1];
		StrCpy(f->SrcPath, sizeof(f->SrcPath), setting.SettingPath);
	}
	else
	{
		// No configuration file
		num_files = 1;
	}

	for (i = 0;i < num_files;i++)
	{
		bool b = true;

		if (i == 0 && setting.DownloadNotRequired)
		{
			b = false;
		}

		if (b)
		{
			wchar_t tmp[MAX_SIZE];
			IO *dest = NULL;
			VI_FILE *down;
			UINT ret;
			UINT totalsize;
			UINT currentsize;
			wchar_t filename_w[MAX_PATH];

			f = &files[i];
			GetFileNameFromFilePath(f->FileName, sizeof(f->FileName), f->SrcPath);
			MakeSafeFileName(f->FileName, sizeof(f->FileName), f->FileName);

			StrToUni(filename_w, sizeof(filename_w), f->FileName);
			ConbinePathW(f->DestPathW, sizeof(f->DestPathW), MsGetMyTempDirW(), filename_w);

			ViInstallDlgSetPos(hWnd, 0);
			UniFormat(tmp, sizeof(tmp), _U(IDS_DOWNLOADSTART+skip), f->FileName);
			ViInstallDlgSetText(d, hWnd, S_STATUS, tmp);

			down = ViOpenFile(f->SrcPath);
			if (down == NULL)
			{
				MsgBoxEx(hWnd, MB_ICONSTOP, _U(IDS_DOWNLOAD_ERROR+skip), f->FileName);

				ViInstallDlgCancel(hWnd);
				return;
			}

			dest = FileCreateW(f->DestPathW);
			if (dest == NULL)
			{
				MsgBoxEx(hWnd, MB_ICONSTOP, _U(IDS_TEMP_ERROR+skip), f->DestPathW);

				ViCloseFile(down);
				ViInstallDlgCancel(hWnd);
				return;
			}

			totalsize = ViGetFileSize(down);
			currentsize = 0;

			UniFormat(tmp, sizeof(tmp), _U(IDS_DOWNLOADING3+skip), f->FileName);
			ViInstallDlgSetText(d, hWnd, S_STATUS, tmp);

			while (true)
			{
				UINT pos = 0;

				if (d->Halt)
				{
					// User cancel
					FileClose(dest);
					ViCloseFile(down);
					return;
				}

				UniFormat(tmp, sizeof(tmp), _U(IDS_DOWNLOADING3+skip), f->FileName);

				ViInstallDlgSetText(d, hWnd, IDS_DOWNLOADING3+skip, tmp);
				ret = ViReadFile(down, d->Buf, d->BufSize);

				if (ret == INFINITE)
				{
					// Communication error
					MsgBoxEx(hWnd, MB_ICONSTOP, _U(IDS_DOWNLOAD_ERROR+skip), f->FileName);

					FileClose(dest);
					ViCloseFile(down);
					ViInstallDlgCancel(hWnd);

					return;
				}

				// Draw progress
				currentsize += ret;

				if (totalsize != 0)
				{
					UniFormat(tmp, sizeof(tmp), _U(IDS_DOWNLOADING+skip),
						((float)totalsize) / 1024.0f / 1024.0f,
						((float)currentsize) / 1024.0f / 1024.0f);

					pos = (UINT)(((float)currentsize) * 100.0f / ((float)totalsize));
				}
				else
				{
					UniFormat(tmp, sizeof(tmp), _U(IDS_DOWNLOADING2+skip),
						((float)currentsize) / 1024.0f / 1024.0f);
					pos = (UINT)(((float)currentsize) * 100.0f / (1024.0f * 1024.0f * 10.0f));
				}

				ViInstallDlgSetText(d, hWnd, S_SIZEINFO, tmp);
				ViInstallDlgSetPos(hWnd, pos);

				if (ret == 0)
				{
					// Download Complete
					break;
				}
				else
				{
					FileWrite(dest, d->Buf, ret);
				}
			}

			ViCloseFile(down);
			FileClose(dest);
		}
	}

	UniStrCpy(setting.DownloadedInstallerPathW, sizeof(setting.DownloadedInstallerPathW),
		files[0].DestPathW);

	if (num_files >= 2)
	{
		UniStrCpy(setting.DownloadedSettingPathW, sizeof(setting.DownloadedSettingPathW),
			files[1].DestPathW);
	}

	PostMessageA(hWnd, WM_VI_DOWNLOAD_FINISHED, 0, 0);
}