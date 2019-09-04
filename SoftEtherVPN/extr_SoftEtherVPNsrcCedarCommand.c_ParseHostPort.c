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
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ UINT ;
struct TYPE_4__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;

/* Variables and functions */
 char* CopyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 scalar_t__ INFINITE ; 
 scalar_t__ InStr (char*,char*) ; 
 int IsEmptyStr (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int ParseHostPortAtmark (char*,char**,scalar_t__*,scalar_t__) ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 scalar_t__ SearchStrEx (char*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ StrLen (char*) ; 
 scalar_t__ ToInt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Trim (char*) ; 

bool ParseHostPort(char *src, char **host, UINT *port, UINT default_port)
{
	TOKEN_LIST *t;
	bool ret = false;
	// Validate arguments
	if (src == NULL)
	{
		return false;
	}

	if (StartWith(src, "["))
	{
		if (InStr(src, "]"))
		{
			// Format of [target]:port
			UINT i, n;
			char tmp[MAX_SIZE];

			StrCpy(tmp, sizeof(tmp), src);

			n = SearchStrEx(tmp, "]", 0, false);
			if (n != INFINITE)
			{
				UINT len = StrLen(tmp);

				for (i = n;i < len;i++)
				{
					if (tmp[i] == ':')
					{
						tmp[i] = '@';
					}
				}
			}

			return ParseHostPortAtmark(tmp, host, port, default_port);
		}
	}

	if (InStr(src, "@"))
	{
		// It is separated by @
		return ParseHostPortAtmark(src, host, port, default_port);
	}

	t = ParseToken(src, ":");
	if (t == NULL)
	{
		return false;
	}

	if (port != NULL)
	{
		*port = 0;
	}

	if (default_port == 0)
	{
		if (t->NumTokens < 2)
		{
			FreeToken(t);
			return false;
		}

		if (ToInt(t->Token[1]) == 0)
		{
			FreeToken(t);
			return false;
		}
	}

	if (t->NumTokens >= 2 && ToInt(t->Token[1]) == 0)
	{
		FreeToken(t);
		return false;
	}

	if (t->NumTokens >= 1 && IsEmptyStr(t->Token[0]) == false)
	{
		ret = true;

		if (host != NULL)
		{
			*host = CopyStr(t->Token[0]);
			Trim(*host);
		}

		if (t->NumTokens >= 2)
		{
			if (port != NULL)
			{
				*port = ToInt(t->Token[1]);
			}
		}
	}

	if (port != NULL)
	{
		if (*port == 0)
		{
			*port = default_port;
		}
	}

	FreeToken(t);

	return ret;
}