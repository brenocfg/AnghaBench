#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  size ;
typedef  int /*<<< orphan*/  fullpath ;
typedef  int /*<<< orphan*/  exedir ;
typedef  int /*<<< orphan*/  errorcode ;
struct TYPE_4__ {int InternetFile; int FileSize; int /*<<< orphan*/ * io; int /*<<< orphan*/ * hHttpFile; int /*<<< orphan*/ * hInternet; } ;
typedef  TYPE_1__ VI_FILE ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IO ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ConbinePath (char*,int,char*,char*) ; 
 int /*<<< orphan*/  DEFAULT_USER_AGENT ; 
 int /*<<< orphan*/ * FileOpen (char*,int) ; 
 int FileSize (int /*<<< orphan*/ *) ; 
 int FtpGetFileSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetExeDir (char*,int) ; 
 int HTTP_QUERY_CONTENT_LENGTH ; 
 int HTTP_QUERY_FLAG_NUMBER ; 
 int HTTP_QUERY_STATUS_CODE ; 
 int HttpQueryInfo (int /*<<< orphan*/ *,int,int*,int*,int /*<<< orphan*/ *) ; 
 int INTERNET_FLAG_NO_CACHE_WRITE ; 
 int INTERNET_FLAG_RELOAD ; 
 int /*<<< orphan*/  INTERNET_OPEN_TYPE_PRECONFIG ; 
 int /*<<< orphan*/  InternetCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InternetOpenA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * InternetOpenUrlA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 scalar_t__ StartWith (char*,char*) ; 
 scalar_t__ ViIsInternetFile (char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

VI_FILE *ViOpenFile(char *path)
{
	VI_FILE *f;
	// Validate arguments
	if (path == NULL)
	{
		return NULL;
	}

	if (ViIsInternetFile(path))
	{
		HINTERNET hHttpFile;
		HINTERNET hInternet = InternetOpenA(DEFAULT_USER_AGENT,
			INTERNET_OPEN_TYPE_PRECONFIG,
			NULL, NULL, 0);
		UINT size;
		UINT sizesize;

		if (hInternet == NULL)
		{
			return NULL;
		}

		hHttpFile = InternetOpenUrlA(hInternet, path, NULL, 0,
			INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_RELOAD, 0);

		if (hHttpFile == NULL)
		{
			InternetCloseHandle(hInternet);
			return NULL;
		}

		size = 0;
		sizesize = sizeof(size);

		if (StartWith(path, "ftp://"))
		{
			// ftp
			DWORD high = 0;

			size = FtpGetFileSize(hHttpFile, &high);
		}
		else
		{
			UINT errorcode = 0;
			UINT errorcode_size = sizeof(errorcode);

			// http
			if (HttpQueryInfo(hHttpFile, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER,
				&size, &sizesize, NULL) == false)
			{
				size = 0;
			}

			if (HttpQueryInfo(hHttpFile, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
				&errorcode, &errorcode_size, NULL) == false ||
				(errorcode / 100) != 2)
			{
				// HTTP getting error
				InternetCloseHandle(hInternet);
				InternetCloseHandle(hHttpFile);
				return NULL;
			}
		}

		f = ZeroMalloc(sizeof(VI_FILE));
		f->InternetFile = true;
		f->hInternet = hInternet;
		f->hHttpFile = hHttpFile;
		f->FileSize = size;

		return f;
	}
	else
	{
		IO *io;
		char fullpath[MAX_PATH];
		char exedir[MAX_PATH];

		GetExeDir(exedir, sizeof(exedir));

		ConbinePath(fullpath, sizeof(fullpath), exedir, path);

		io = FileOpen(fullpath, false);
		if (io == NULL)
		{
			return NULL;
		}

		f = ZeroMalloc(sizeof(VI_FILE));
		f->InternetFile = false;
		f->FileSize = FileSize(io);
		f->io = io;

		return f;
	}
}