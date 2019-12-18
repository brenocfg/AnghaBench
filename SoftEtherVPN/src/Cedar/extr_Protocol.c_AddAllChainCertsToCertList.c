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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  exedir ;
typedef  int /*<<< orphan*/  dirname ;
typedef  int /*<<< orphan*/  X ;
typedef  size_t UINT ;
struct TYPE_6__ {int Folder; char* FileNameW; } ;
struct TYPE_5__ {size_t NumFiles; TYPE_2__** File; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ DIRLIST ;
typedef  TYPE_2__ DIRENT ;

/* Variables and functions */
 int /*<<< orphan*/  AddXToCertList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CombinePathW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* EnumDirW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileToXW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeDir (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetExeDirW (int /*<<< orphan*/ *,int) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MakeDirExW (int /*<<< orphan*/ *) ; 

void AddAllChainCertsToCertList(LIST *o)
{
	wchar_t dirname[MAX_SIZE];
	wchar_t exedir[MAX_SIZE];
	DIRLIST *dir;
	// Validate arguments
	if (o == NULL)
	{
		return;
	}

	GetExeDirW(exedir, sizeof(exedir));

	CombinePathW(dirname, sizeof(dirname), exedir, L"chain_certs");

	MakeDirExW(dirname);

	dir = EnumDirW(dirname);

	if (dir != NULL)
	{
		UINT i;

		for (i = 0;i < dir->NumFiles;i++)
		{
			DIRENT *e = dir->File[i];

			if (e->Folder == false)
			{
				wchar_t tmp[MAX_SIZE];
				X *x;

				CombinePathW(tmp, sizeof(tmp), dirname, e->FileNameW);

				x = FileToXW(tmp);

				if (x != NULL)
				{
					AddXToCertList(o, x);

					FreeX(x);
				}
			}
		}

		FreeDir(dir);
	}
}