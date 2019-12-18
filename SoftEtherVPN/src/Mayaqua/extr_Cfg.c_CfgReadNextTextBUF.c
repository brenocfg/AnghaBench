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
typedef  char wchar_t ;
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int B64_Decode (void*,char*,int) ; 
 scalar_t__ CalcUtf8ToUni (char*,int) ; 
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  CfgAddByte (int /*<<< orphan*/ *,char*,void*,int) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  CfgAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddUniStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 char* CfgReadNextLine (int /*<<< orphan*/ *) ; 
 char* CfgUnescape (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 void* Malloc (int) ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 int /*<<< orphan*/  StrCmpi (char*,char*) ; 
 int StrLen (char*) ; 
 char* TAG_BOOL ; 
 char* TAG_BYTE ; 
 char* TAG_DECLARE ; 
 char* TAG_INT ; 
 char* TAG_INT64 ; 
 char* TAG_STRING ; 
 char* TAG_TRUE ; 
 scalar_t__ ToInt (char*) ; 
 int /*<<< orphan*/  ToInt64 (char*) ; 
 int /*<<< orphan*/  Utf8ToUni (char*,scalar_t__,char*,int) ; 

bool CfgReadNextTextBUF(BUF *b, FOLDER *current)
{
	char *buf;
	TOKEN_LIST *token;
	char *name;
	char *string;
	char *data;
	bool ret;
	FOLDER *f;

	// Validate arguments
	if (b == NULL || current == NULL)
	{
		return false;
	}

	ret = true;

	// Read one line
	buf = CfgReadNextLine(b);
	if (buf == NULL)
	{
		return false;
	}

	// Analyze this line
	token = ParseToken(buf, "\t ");
	if (token == NULL)
	{
		Free(buf);
		return false;
	}

	if (token->NumTokens >= 1)
	{
		if (!StrCmpi(token->Token[0], TAG_DECLARE))
		{
			if (token->NumTokens >= 2)
			{
				// declare
				name = CfgUnescape(token->Token[1]);

				// Create a folder
				f = CfgCreateFolder(current, name);

				// Read the next folder
				while (true)
				{
					if (CfgReadNextTextBUF(b, f) == false)
					{
						break;
					}
				}

				Free(name);
			}
		}
		if (!StrCmpi(token->Token[0], "}"))
		{
			// end
			ret = false;
		}
		if (token->NumTokens >= 3)
		{
			name = CfgUnescape(token->Token[1]);
			data = token->Token[2];

			if (!StrCmpi(token->Token[0], TAG_STRING))
			{
				// string
				wchar_t *uni;
				UINT uni_size;
				string = CfgUnescape(data);
				uni_size = CalcUtf8ToUni(string, StrLen(string));
				if (uni_size != 0)
				{
					uni = Malloc(uni_size);
					Utf8ToUni(uni, uni_size, string, StrLen(string));
					CfgAddUniStr(current, name, uni);
					Free(uni);
				}
				Free(string);
			}
			if (!StrCmpi(token->Token[0], TAG_INT))
			{
				// uint
				CfgAddInt(current, name, ToInt(data));
			}
			if (!StrCmpi(token->Token[0], TAG_INT64))
			{
				// uint64
				CfgAddInt64(current, name, ToInt64(data));
			}
			if (!StrCmpi(token->Token[0], TAG_BOOL))
			{
				// bool
				bool b = false;
				if (!StrCmpi(data, TAG_TRUE))
				{
					b = true;
				}
				else if (ToInt(data) != 0)
				{
					b = true;
				}
				CfgAddBool(current, name, b);
			}
			if (!StrCmpi(token->Token[0], TAG_BYTE))
			{
				// byte
				char *unescaped_b64 = CfgUnescape(data);
				void *tmp = Malloc(StrLen(unescaped_b64) * 4 + 64);
				int size = B64_Decode(tmp, unescaped_b64, StrLen(unescaped_b64));
				CfgAddByte(current, name, tmp, size);
				Free(tmp);
				Free(unescaped_b64);
			}

			Free(name);
		}
	}

	// Release of the token
	FreeToken(token);

	Free(buf);

	return ret;
}