#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  exe_dir ;
typedef  int /*<<< orphan*/  dir_name ;
typedef  size_t UINT ;
struct TYPE_6__ {char* FileName; scalar_t__ Folder; } ;
struct TYPE_5__ {size_t NumFiles; TYPE_2__** File; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ DIRLIST ;
typedef  TYPE_2__ DIRENT ;

/* Variables and functions */
 int /*<<< orphan*/  CmpLogFile ; 
 TYPE_1__* EnumDir (char*) ; 
 int /*<<< orphan*/  EnumLogFileDir (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*) ; 
 int /*<<< orphan*/  FreeDir (TYPE_1__*) ; 
 int /*<<< orphan*/  GetExeDir (char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 scalar_t__ StrLen (char*) ; 

LIST *EnumLogFile(char *hubname)
{
	char exe_dir[MAX_PATH];
	char tmp[MAX_PATH];
	LIST *o = NewListFast(CmpLogFile);
	DIRLIST *dir;

	if (StrLen(hubname) == 0)
	{
		hubname = NULL;
	}

	GetExeDir(exe_dir, sizeof(exe_dir));

	// Enumerate in the server_log
	if (hubname == NULL)
	{
		EnumLogFileDir(o, "server_log");
	}

	// Enumerate in the packet_log
	Format(tmp, sizeof(tmp), "%s/packet_log", exe_dir);
	dir = EnumDir(tmp);
	if (dir != NULL)
	{
		UINT i;
		for (i = 0;i < dir->NumFiles;i++)
		{
			DIRENT *e = dir->File[i];

			if (e->Folder)
			{
				char dir_name[MAX_PATH];

				if (hubname == NULL || StrCmpi(hubname, e->FileName) == 0)
				{
					Format(dir_name, sizeof(dir_name), "packet_log/%s", e->FileName);
					EnumLogFileDir(o, dir_name);
				}
			}
		}

		FreeDir(dir);
	}

	// Enumerate in the security_log
	Format(tmp, sizeof(tmp), "%s/security_log", exe_dir);
	dir = EnumDir(tmp);
	if (dir != NULL)
	{
		UINT i;
		for (i = 0;i < dir->NumFiles;i++)
		{
			DIRENT *e = dir->File[i];

			if (e->Folder)
			{
				char dir_name[MAX_PATH];

				if (hubname == NULL || StrCmpi(hubname, e->FileName) == 0)
				{
					Format(dir_name, sizeof(dir_name), "security_log/%s", e->FileName);
					EnumLogFileDir(o, dir_name);
				}
			}
		}

		FreeDir(dir);
	}

	return o;
}