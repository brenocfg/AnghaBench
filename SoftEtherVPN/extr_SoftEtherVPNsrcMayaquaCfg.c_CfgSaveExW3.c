#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_9__ {int /*<<< orphan*/  OsType; } ;
struct TYPE_8__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  LashHash; } ;
typedef  int /*<<< orphan*/  IO ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ CFG_RW ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 TYPE_2__* CfgFolderToBuf (int /*<<< orphan*/ *,int) ; 
 scalar_t__ Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileCopyExWithEofW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * FileCreateW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileDeleteW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FileRenameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int FileWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 TYPE_3__* GetOsInfo () ; 
 int MAX_SIZE ; 
 scalar_t__ OS_IS_UNIX (int /*<<< orphan*/ ) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ ,int) ; 

bool CfgSaveExW3(CFG_RW *rw, FOLDER *f, wchar_t *name, UINT *written_size, bool write_binary)
{
	wchar_t tmp[MAX_SIZE];
	bool text = !write_binary;
	UCHAR hash[SHA1_SIZE];
	BUF *b;
	IO *o;
	bool ret = true;
	UINT dummy_int = 0;
	// Validate arguments
	if (name == NULL || f == NULL)
	{
		return false;
	}
	if (written_size == NULL)
	{
		written_size = &dummy_int;
	}

	// Convert to buffer
	b = CfgFolderToBuf(f, text);
	if (b == NULL)
	{
		return false;
	}
	// Hash the contents
	Sha0(hash, b->Buf, b->Size);

	// Compare the contents to be written with the content which was written last
	if (rw != NULL)
	{
		if (Cmp(hash, rw->LashHash, SHA1_SIZE) == 0)
		{
			// Contents are not changed
			ret = false;
		}
		else
		{
			Copy(rw->LashHash, hash, SHA1_SIZE);
		}
	}

	if (ret || OS_IS_UNIX(GetOsInfo()->OsType))
	{
		// Generate a temporary file name
		UniFormat(tmp, sizeof(tmp), L"%s.log", name);
		// Copy the file that currently exist to a temporary file
		// with appending the EOF
		FileCopyExWithEofW(name, tmp, true);

		// Save the new file
		o = FileCreateW(name);
		if (o != NULL)
		{
			if (FileWrite(o, b->Buf, b->Size) == false)
			{
				// File saving failure
				FileClose(o);
				FileDeleteW(name);
				FileRenameW(tmp, name);

				if (rw != NULL)
				{
					Zero(rw->LashHash, sizeof(rw->LashHash));
				}
			}
			else
			{
				// Successful saving file
				FileClose(o);

				// Delete the temporary file
				FileDeleteW(tmp);
			}
		}
		else
		{
			// File saving failure
			FileRenameW(tmp, name);

			if (rw != NULL)
			{
				Zero(rw->LashHash, sizeof(rw->LashHash));
			}
		}
	}

	*written_size = b->Size;

	// Release memory 
	FreeBuf(b);

	return ret;
}