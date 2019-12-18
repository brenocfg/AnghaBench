#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  hex_a ;
typedef  int /*<<< orphan*/  hex ;
typedef  int /*<<< orphan*/  fn ;
typedef  int /*<<< orphan*/  exedir ;
typedef  int /*<<< orphan*/  dirname ;
struct TYPE_17__ {scalar_t__ root_cert; int /*<<< orphan*/  subject_name; } ;
typedef  TYPE_1__ X ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_19__ {int Folder; char* FileNameW; } ;
struct TYPE_18__ {size_t NumFiles; TYPE_3__** File; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ DIRLIST ;
typedef  TYPE_3__ DIRENT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_DOWNLOAD_CERTS_PREFIX ; 
 int /*<<< orphan*/  AddAllChainCertsToCertList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BinToStr (char*,int,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* CloneX (TYPE_1__*) ; 
 int /*<<< orphan*/  CombinePathW (char*,int,char*,char*) ; 
 int CompareX (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  Debug (char*,size_t,char*) ; 
 int /*<<< orphan*/  DumpBufW (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* EnumDirW (char*) ; 
 int /*<<< orphan*/  FileDeleteW (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeCertList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeDir (TYPE_2__*) ; 
 int /*<<< orphan*/  GetAllNameFromName (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetExeDirW (char*,int) ; 
 int /*<<< orphan*/  GetXDigest (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int IsXInCertList (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,size_t) ; 
 size_t LIST_NUM (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MakeDirExW (char*) ; 
 int /*<<< orphan*/ * NewCertList (int) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  StrToUni (char*,int,char*) ; 
 int TryGetParentCertFromCertList (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ UniStartWith (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCat (char*,int,char*) ; 
 int /*<<< orphan*/  UniStrCpy (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XToBuf (TYPE_1__*,int) ; 

bool TryGetRootCertChain(LIST *o, X *x, bool auto_save, X **found_root_x)
{
	bool ret = false;
	LIST *chain = NULL;
	LIST *current_chain_dir = NULL;
	// Validate arguments
	if (o == NULL || x == NULL)
	{
		return false;
	}

	chain = NewCertList(false);

	ret = TryGetParentCertFromCertList(o, x, chain);

	if (ret)
	{
		UINT i;
		DIRLIST *dir;
		wchar_t dirname[MAX_SIZE];
		wchar_t exedir[MAX_SIZE];

		GetExeDirW(exedir, sizeof(exedir));
		CombinePathW(dirname, sizeof(dirname), exedir, L"chain_certs");
		MakeDirExW(dirname);

		if (auto_save)
		{
			// delete the current auto_save files
			dir = EnumDirW(dirname);
			if (dir != NULL)
			{
				for (i = 0;i < dir->NumFiles;i++)
				{
					DIRENT *e = dir->File[i];

					if (e->Folder == false)
					{
						if (UniStartWith(e->FileNameW, AUTO_DOWNLOAD_CERTS_PREFIX))
						{
							wchar_t tmp[MAX_SIZE];

							CombinePathW(tmp, sizeof(tmp), dirname, e->FileNameW);

							FileDeleteW(tmp);
						}
					}
				}

				FreeDir(dir);
			}
		}

		current_chain_dir = NewCertList(false);
		AddAllChainCertsToCertList(current_chain_dir);

		for (i = 0;i < LIST_NUM(chain);i++)
		{
			wchar_t tmp[MAX_SIZE];
			X *xx = LIST_DATA(chain, i);

			GetAllNameFromName(tmp, sizeof(tmp), xx->subject_name);

			Debug("depth = %u, subject = %S\n", i, tmp);

			if (auto_save && CompareX(x, xx) == false && IsXInCertList(current_chain_dir, xx) == false)
			{
				wchar_t fn[MAX_PATH];
				char hex_a[128];
				wchar_t hex[128];
				UCHAR hash[SHA1_SIZE];
				wchar_t tmp[MAX_SIZE];
				BUF *b;

				GetXDigest(xx, hash, true);
				BinToStr(hex_a, sizeof(hex_a), hash, SHA1_SIZE);
				StrToUni(hex, sizeof(hex), hex_a);

				UniStrCpy(fn, sizeof(fn), AUTO_DOWNLOAD_CERTS_PREFIX);
				UniStrCat(fn, sizeof(fn), hex);
				UniStrCat(fn, sizeof(fn), L".cer");

				CombinePathW(tmp, sizeof(tmp), dirname, fn);

				b = XToBuf(xx, true);

				DumpBufW(b, tmp);

				FreeBuf(b);
			}

			if (xx->root_cert)
			{
				if (found_root_x != NULL)
				{
					*found_root_x = CloneX(xx);
				}
			}
		}
	}

	FreeCertList(chain);

	FreeCertList(current_chain_dir);

	return ret;
}