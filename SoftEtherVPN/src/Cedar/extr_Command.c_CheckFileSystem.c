#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  exe_dir ;
typedef  int /*<<< orphan*/  exe ;
typedef  size_t UINT ;
typedef  size_t UCHAR ;
struct TYPE_10__ {size_t Size; scalar_t__ Buf; } ;
struct TYPE_9__ {size_t NumFiles; TYPE_1__** File; } ;
struct TYPE_8__ {int /*<<< orphan*/  FileName; } ;
typedef  int /*<<< orphan*/  IO ;
typedef  TYPE_2__ DIRLIST ;
typedef  TYPE_3__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CombinePathW (char*,int,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ EndWith (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* EnumDir (char*) ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileCreateW (char*) ; 
 int /*<<< orphan*/  FileDeleteW (char*) ; 
 int /*<<< orphan*/ * FileOpenW (char*,int) ; 
 int FileSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileWrite (int /*<<< orphan*/ *,size_t*,size_t) ; 
 int /*<<< orphan*/  Free (size_t*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeDir (TYPE_2__*) ; 
 int /*<<< orphan*/  GetExeDir (char*,int) ; 
 int /*<<< orphan*/  GetExeName (char*,int) ; 
 int MAX_PATH ; 
 size_t* Malloc (size_t) ; 
 int /*<<< orphan*/  MsGetMyTempDirW () ; 
 int /*<<< orphan*/  Print (char*) ; 
 TYPE_3__* ReadDumpW (char*) ; 

bool CheckFileSystem()
{
	bool ok = false;
	char exe[MAX_PATH];
	char exe_dir[MAX_PATH];
	DIRLIST *dirs;
	UINT i;

	GetExeName(exe, sizeof(exe));
	GetExeDir(exe_dir, sizeof(exe_dir));

	dirs = EnumDir(exe_dir);
	for (i = 0;i < dirs->NumFiles;i++)
	{
		if (EndWith(exe, dirs->File[i]->FileName))
		{
			ok = true;
			break;
		}
	}
	FreeDir(dirs);

	if (ok == false)
	{
		Print("EnumDir Failed.\n");
		return false;
	}
	else
	{
		UINT size = 1234567;
		UCHAR *buf;
		IO *io;
#ifndef	OS_WIN32
		wchar_t *filename = L"/tmp/vpn_checker_tmp";
#else	// OS_WIN32
		wchar_t filename[MAX_PATH];
		CombinePathW(filename, sizeof(filename), MsGetMyTempDirW(), L"vpn_checker_tmp");
#endif	// OS_WIN32

		buf = Malloc(size);
		for (i = 0;i < size;i++)
		{
			buf[i] = i % 256;
		}

		io = FileCreateW(filename);
		if (io == NULL)
		{
			Print("FileCreate Failed.\n");
			Free(buf);
			return false;
		}
		else
		{
			FileWrite(io, buf, size);
			Free(buf);
			FileClose(io);

			io = FileOpenW(filename, false);
			if (FileSize(io) != 1234567)
			{
				Print("FileSize Failed.\n");
				FileClose(io);
				return false;
			}
			else
			{
				BUF *b;

				FileClose(io);
				b = ReadDumpW(filename);
				if(b == NULL)
				{
					return false;
				}

				for (i = 0;i < b->Size;i++)
				{
					UCHAR c = ((UCHAR *)b->Buf)[i];

					if (c != (i % 256))
					{
						Print("FileToBuf Failed.\n");
						FreeBuf(b);
						return false;
					}
				}

				FreeBuf(b);
			}
		}

		FileDeleteW(filename);
	}

	return ok;
}