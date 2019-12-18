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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  str_size ;
typedef  int /*<<< orphan*/  num ;
typedef  int /*<<< orphan*/  header ;
typedef  int /*<<< orphan*/  exe_dir ;
typedef  scalar_t__ UINT ;
struct TYPE_4__ {char Size; char SizeCompressed; char Offset; int /*<<< orphan*/  FileName; } ;
typedef  TYPE_1__ HC ;

/* Variables and functions */
 scalar_t__ Cmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CompareHamcore ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 scalar_t__ Endian32 (scalar_t__) ; 
 int /*<<< orphan*/  FileClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * FileOpenW (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FileRead (int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  FileReplaceRenameW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetExeDirW (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HAMCORE_FILE_NAME ; 
 int /*<<< orphan*/  HAMCORE_FILE_NAME_2 ; 
 int /*<<< orphan*/  HAMCORE_HEADER_DATA ; 
 int HAMCORE_HEADER_SIZE ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int MAX_PATH ; 
 int MAX_SIZE ; 
 scalar_t__ MayaquaIsMinimalMode () ; 
 int /*<<< orphan*/  MsGetSystem32Dir () ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 
 int /*<<< orphan*/  hamcore ; 
 int /*<<< orphan*/ * hamcore_io ; 

void InitHamcore()
{
	wchar_t tmp[MAX_PATH];
	wchar_t tmp2[MAX_PATH];
	wchar_t exe_dir[MAX_PATH];
	UINT i, num;
	char header[HAMCORE_HEADER_SIZE];

	hamcore = NewList(CompareHamcore);

	if (MayaquaIsMinimalMode())
	{
		return;
	}

	GetExeDirW(exe_dir, sizeof(exe_dir));
	UniFormat(tmp, sizeof(tmp), L"%s/%S", exe_dir, HAMCORE_FILE_NAME);

	UniFormat(tmp2, sizeof(tmp2), L"%s/%S", exe_dir, HAMCORE_FILE_NAME_2);

	// If there is _hamcore.se2, overwrite it yo the hamcore.se2 
	FileReplaceRenameW(tmp2, tmp);

	// Read if there is a file hamcore.se2
	hamcore_io = FileOpenW(tmp, false);
	if (hamcore_io == NULL)
	{
		// Look in other locations if it isn't found
#ifdef	OS_WIN32
		UniFormat(tmp, sizeof(tmp), L"%S/%S", MsGetSystem32Dir(), HAMCORE_FILE_NAME);
#else	// OS_WIN32
		UniFormat(tmp, sizeof(tmp), L"/bin/%S", HAMCORE_FILE_NAME);
#endif	// OS_WIN32

		hamcore_io = FileOpenW(tmp, false);
		if (hamcore_io == NULL)
		{
			return;
		}
	}

	// Read the file header
	Zero(header, sizeof(header));
	FileRead(hamcore_io, header, HAMCORE_HEADER_SIZE);

	if (Cmp(header, HAMCORE_HEADER_DATA, HAMCORE_HEADER_SIZE) != 0)
	{
		// Invalid header
		FileClose(hamcore_io);
		hamcore_io = NULL;
		return;
	}

	// The number of the File
	num = 0;
	FileRead(hamcore_io, &num, sizeof(num));
	num = Endian32(num);
	for (i = 0;i < num;i++)
	{
		// File name
		char tmp[MAX_SIZE];
		UINT str_size = 0;
		HC *c;

		FileRead(hamcore_io, &str_size, sizeof(str_size));
		str_size = Endian32(str_size);
		if (str_size >= 1)
		{
			str_size--;
		}

		Zero(tmp, sizeof(tmp));
		FileRead(hamcore_io, tmp, str_size);

		c = ZeroMalloc(sizeof(HC));
		c->FileName = CopyStr(tmp);

		FileRead(hamcore_io, &c->Size, sizeof(UINT));
		c->Size = Endian32(c->Size);

		FileRead(hamcore_io, &c->SizeCompressed, sizeof(UINT));
		c->SizeCompressed = Endian32(c->SizeCompressed);

		FileRead(hamcore_io, &c->Offset, sizeof(UINT));
		c->Offset = Endian32(c->Offset);

		Insert(hamcore, c);
	}
}