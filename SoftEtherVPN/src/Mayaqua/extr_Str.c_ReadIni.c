#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_3__ {void* UnicodeValue; void* Value; void* Key; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ INI_ENTRY ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int CalcUtf8ToUni (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 void* CopyStr (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 scalar_t__ GetKeyAndValue (char*,char*,int,char*,int,int /*<<< orphan*/ *) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SeekBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  Utf8ToUni (void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* ZeroMalloc (int) ; 

LIST *ReadIni(BUF *b)
{
	LIST *o;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	o = NewListFast(NULL);

	SeekBuf(b, 0, 0);

	while (true)
	{
		char *line = CfgReadNextLine(b);

		if (line == NULL)
		{
			break;
		}

		Trim(line);

		if (IsEmptyStr(line) == false)
		{
			if (StartWith(line, "#") == false &&
				StartWith(line, "//") == false &&
				StartWith(line, ";") == false)
			{
				char *key, *value;
				UINT size = StrLen(line) + 1;

				key = ZeroMalloc(size);
				value = ZeroMalloc(size);

				if (GetKeyAndValue(line, key, size, value, size, NULL))
				{
					UINT uni_size;
					INI_ENTRY *e = ZeroMalloc(sizeof(INI_ENTRY));
					e->Key = CopyStr(key);
					e->Value = CopyStr(value);

					uni_size = CalcUtf8ToUni((BYTE *)value, StrLen(value));
					e->UnicodeValue = ZeroMalloc(uni_size);
					Utf8ToUni(e->UnicodeValue, uni_size, (BYTE *)value, StrLen(value));

					Add(o, e);
				}

				Free(key);
				Free(value);
			}
		}

		Free(line);
	}

	return o;
}