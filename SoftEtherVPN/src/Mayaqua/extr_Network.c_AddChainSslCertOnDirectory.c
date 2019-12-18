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
typedef  int /*<<< orphan*/  txtname ;
typedef  int /*<<< orphan*/  tmp ;
struct ssl_ctx_st {int dummy; } ;
typedef  int /*<<< orphan*/  exedir ;
typedef  int /*<<< orphan*/  dirname ;
typedef  int /*<<< orphan*/  X ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_6__ {int Folder; char* FileNameW; } ;
struct TYPE_5__ {size_t NumFiles; TYPE_2__** File; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ DIRLIST ;
typedef  TYPE_2__ DIRENT ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddChainSslCert (struct ssl_ctx_st*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Clone (int /*<<< orphan*/ *,int) ; 
 scalar_t__ Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CombinePathW (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* EnumDirW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileCopyW (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileToXW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeDir (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetExeDirW (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GetXDigest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int IsFileExistsW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,size_t) ; 
 size_t LIST_NUM (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MakeDirExW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int SHA1_SIZE ; 

void AddChainSslCertOnDirectory(struct ssl_ctx_st *ctx)
{
	wchar_t dirname[MAX_SIZE];
	wchar_t exedir[MAX_SIZE];
	wchar_t txtname[MAX_SIZE];
	DIRLIST *dir;
	LIST *o;
	UINT i;

	// Validate arguments
	if (ctx == NULL)
	{
		return;
	}

	o = NewListFast(NULL);

	GetExeDirW(exedir, sizeof(exedir));

	CombinePathW(dirname, sizeof(dirname), exedir, L"chain_certs");

	MakeDirExW(dirname);

	CombinePathW(txtname, sizeof(txtname), dirname, L"Readme_Chain_Certs.txt");

	if (IsFileExistsW(txtname) == false)
	{
		FileCopyW(L"|chain_certs.txt", txtname);
	}

	dir = EnumDirW(dirname);

	if (dir != NULL)
	{
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
					UINT j;
					bool exists = false;
					UCHAR hash[SHA1_SIZE];

					GetXDigest(x, hash, true);

					for (j = 0;j < LIST_NUM(o);j++)
					{
						UCHAR *hash2 = LIST_DATA(o, j);

						if (Cmp(hash, hash2, SHA1_SIZE) == 0)
						{
							exists = true;
						}
					}

					if (exists == false)
					{
						AddChainSslCert(ctx, x);

						Add(o, Clone(hash, SHA1_SIZE));
					}

					FreeX(x);
				}
			}
		}

		FreeDir(dir);
	}

	for (i = 0;i < LIST_NUM(o);i++)
	{
		UCHAR *hash = LIST_DATA(o, i);

		Free(hash);
	}

	ReleaseList(o);
}