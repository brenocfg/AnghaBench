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
typedef  int /*<<< orphan*/  full_path ;
typedef  int /*<<< orphan*/  file_path ;
typedef  int /*<<< orphan*/  exe_dir ;
typedef  int /*<<< orphan*/  dir_full_path ;
typedef  size_t UINT ;
struct TYPE_10__ {int Folder; scalar_t__ FileSize; char* FileName; int /*<<< orphan*/  UpdateDate; } ;
struct TYPE_9__ {size_t NumFiles; TYPE_3__** File; } ;
struct TYPE_8__ {size_t FileSize; int /*<<< orphan*/  ServerName; int /*<<< orphan*/  UpdatedTime; int /*<<< orphan*/  Path; } ;
typedef  TYPE_1__ LOG_FILE ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ DIRLIST ;
typedef  TYPE_3__ DIRENT ;

/* Variables and functions */
 scalar_t__ EndWith (char*,char*) ; 
 TYPE_2__* EnumDir (char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  FreeDir (TYPE_2__*) ; 
 int /*<<< orphan*/  GetExeDir (char*,int) ; 
 int /*<<< orphan*/  GetMachineName (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int MAX_PATH ; 
 scalar_t__ MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void EnumLogFileDir(LIST *o, char *dirname)
{
	UINT i;
	char exe_dir[MAX_PATH];
	char dir_full_path[MAX_PATH];
	DIRLIST *dir;
	// Validate arguments
	if (o == NULL || dirname == NULL)
	{
		return;
	}

	GetExeDir(exe_dir, sizeof(exe_dir));
	Format(dir_full_path, sizeof(dir_full_path), "%s/%s", exe_dir, dirname);

	dir = EnumDir(dir_full_path);
	if (dir == NULL)
	{
		return;
	}

	for (i = 0;i < dir->NumFiles;i++)
	{
		DIRENT *e = dir->File[i];

		if (e->Folder == false && e->FileSize > 0)
		{
			char full_path[MAX_PATH];
			char file_path[MAX_PATH];

			Format(file_path, sizeof(file_path), "%s/%s", dirname, e->FileName);
			Format(full_path, sizeof(full_path), "%s/%s", exe_dir, file_path);

			if (EndWith(file_path, ".log"))
			{
				LOG_FILE *f = ZeroMalloc(sizeof(LOG_FILE));

				StrCpy(f->Path, sizeof(f->Path), file_path);
				f->FileSize = (UINT)(MIN(e->FileSize, 0xffffffffUL));
				f->UpdatedTime = e->UpdateDate;

				GetMachineName(f->ServerName, sizeof(f->ServerName));

				Insert(o, f);
			}
		}
	}

	FreeDir(dir);
}