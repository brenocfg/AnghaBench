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
typedef  int /*<<< orphan*/  tmp ;
typedef  size_t UINT ;
struct TYPE_10__ {int Folder; int /*<<< orphan*/  UpdateDate; int /*<<< orphan*/  FileName; } ;
struct TYPE_9__ {size_t NumFiles; TYPE_3__** File; } ;
struct TYPE_8__ {int /*<<< orphan*/  UpdateTime; int /*<<< orphan*/  FullPath; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ ERASE_FILE ;
typedef  TYPE_2__ DIRLIST ;
typedef  TYPE_3__ DIRENT ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 scalar_t__ EndWith (char*,char*) ; 
 TYPE_2__* EnumDir (char*) ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeDir (TYPE_2__*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  NormalizePath (char*,int,char*) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void EnumEraseFile(LIST *o, char *dirname)
{
	DIRLIST *dir;
	UINT i;
	char tmp[MAX_PATH];
	// Validate arguments
	if (o == NULL || dirname == NULL)
	{
		return;
	}

	// Enumeration
	dir = EnumDir(dirname);

	for (i = 0;i < dir->NumFiles;i++)
	{
		DIRENT *e = dir->File[i];
		Format(tmp, sizeof(tmp), "%s/%s", dirname, e->FileName);
		NormalizePath(tmp, sizeof(tmp), tmp);

		if (e->Folder == false)
		{
			// File
			ERASE_FILE *f;

			if (EndWith(tmp, ".log") || EndWith(tmp, ".config") || EndWith(tmp, ".old"))
			{
				// Target only .config files and .log files
				f = ZeroMalloc(sizeof(ERASE_FILE));
				f->FullPath = CopyStr(tmp);
				f->UpdateTime = e->UpdateDate;

				Add(o, f);
			}
		}
		else
		{
			// Folder
			EnumEraseFile(o, tmp);
		}
	}

	FreeDir(dir);
}