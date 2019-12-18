#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ UINT ;
struct TYPE_11__ {int /*<<< orphan*/  Size; } ;
struct TYPE_10__ {int /*<<< orphan*/  TitleLocal; int /*<<< orphan*/  TitleEnglish; int /*<<< orphan*/  Name; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ LANGLIST ;
typedef  TYPE_2__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  AppendBufStr (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  AppendBufUtf8 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int DumpBufWIfNecessary (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeLangList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LANG_CONFIG_TEMPLETE ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LoadLangList () ; 
 int MAX_SIZE ; 
 TYPE_2__* ReadDump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SeekBuf (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool SaveLangConfig(wchar_t *filename, char *str)
{
	BUF *b;
	LIST *o;
	UINT i;
	bool ret;
	// Validate arguments
	if (filename == NULL)
	{
		return false;
	}

	// Read the template
	b = ReadDump(LANG_CONFIG_TEMPLETE);
	if (b == NULL)
	{
		return false;
	}

	SeekBuf(b, b->Size, 0);

	o = LoadLangList();
	if (o != NULL)
	{
		wchar_t tmp[MAX_SIZE];

		AppendBufStr(b, "# Available Language IDs are:\r\n");

		for (i = 0;i < LIST_NUM(o);i++)
		{
			LANGLIST *e = LIST_DATA(o, i);

			UniFormat(tmp, sizeof(tmp), L"#  %S: %s (%s)\r\n",
				e->Name, e->TitleEnglish, e->TitleLocal);

			AppendBufUtf8(b, tmp);
		}

		AppendBufStr(b, "\r\n\r\n# Specify a Language ID here.\r\n");
		AppendBufStr(b, str);
		AppendBufStr(b, "\r\n\r\n");

		FreeLangList(o);
	}

	ret = DumpBufWIfNecessary(b, filename);

	FreeBuf(b);

	return ret;
}