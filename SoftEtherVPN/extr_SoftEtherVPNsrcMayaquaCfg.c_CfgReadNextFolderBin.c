#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CalcUtf8ToUni (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  CfgAddByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  CfgAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
#define  ITEM_TYPE_BOOL 132 
#define  ITEM_TYPE_BYTE 131 
#define  ITEM_TYPE_INT 130 
#define  ITEM_TYPE_INT64 129 
#define  ITEM_TYPE_STRING 128 
 int MAX_SIZE ; 
 int /*<<< orphan*/  ReadBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ReadBufInt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadBufInt64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReadBufStr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  StrLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Utf8ToUni (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZeroMalloc (scalar_t__) ; 

void CfgReadNextFolderBin(BUF *b, FOLDER *parent)
{
	char name[MAX_SIZE];
	FOLDER *f;
	UINT n, i;
	UINT size;
	UCHAR *buf;
	wchar_t *string;
	// Validate arguments
	if (b == NULL || parent == NULL)
	{
		return;
	}

	// Folder name
	ReadBufStr(b, name, sizeof(name));
	f = CfgCreateFolder(parent, name);

	// The number of the subfolder
	n = ReadBufInt(b);
	for (i = 0;i < n;i++)
	{
		// Subfolder
		CfgReadNextFolderBin(b, f);
	}

	// The number of items
	n = ReadBufInt(b);
	for (i = 0;i < n;i++)
	{
		UINT type;

		// Name
		ReadBufStr(b, name, sizeof(name));
		// Type
		type = ReadBufInt(b);

		switch (type)
		{
		case ITEM_TYPE_INT:
			// int
			CfgAddInt(f, name, ReadBufInt(b));
			break;

		case ITEM_TYPE_INT64:
			// int64
			CfgAddInt64(f, name, ReadBufInt64(b));
			break;

		case ITEM_TYPE_BYTE:
			// data
			size = ReadBufInt(b);
			buf = ZeroMalloc(size);
			ReadBuf(b, buf, size);
			CfgAddByte(f, name, buf, size);
			Free(buf);
			break;

		case ITEM_TYPE_STRING:
			// string
			size = ReadBufInt(b);
			buf = ZeroMalloc(size + 1);
			ReadBuf(b, buf, size);
			string = ZeroMalloc(CalcUtf8ToUni(buf, StrLen(buf)) + 4);
			Utf8ToUni(string, 0, buf, StrLen(buf));
			CfgAddUniStr(f, name, string);
			Free(string);
			Free(buf);
			break;

		case ITEM_TYPE_BOOL:
			// bool
			CfgAddBool(f, name, ReadBufInt(b) == 0 ? false : true);
			break;
		}
	}
}