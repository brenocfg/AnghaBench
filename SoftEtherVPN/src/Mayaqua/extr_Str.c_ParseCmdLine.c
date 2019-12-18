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
typedef  size_t UINT ;
struct TYPE_4__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_DATA (int /*<<< orphan*/ *,size_t) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 
 char* Malloc (scalar_t__) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 TYPE_1__* NullToken () ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 size_t StrLen (char*) ; 
 scalar_t__ StrSize (char*) ; 
 void* ZeroMalloc (int) ; 

TOKEN_LIST *ParseCmdLine(char *str)
{
	TOKEN_LIST *t;
	LIST *o;
	UINT i, len, wp, mode;
	char c;
	char *tmp;
	bool ignore_space = false;
	// Validate arguments
	if (str == NULL)
	{
		// There is no token
		return NullToken();
	}

	o = NewListFast(NULL);
	tmp = Malloc(StrSize(str) + 32);

	wp = 0;
	mode = 0;

	len = StrLen(str);
	for (i = 0;i < len;i++)
	{
		c = str[i];

		switch (mode)
		{
		case 0:
			// Mode to discover the next token
			if (c == ' ' || c == '\t')
			{
				// Advance to the next character
			}
			else
			{
				// Start of the token
				if (c == '\"')
				{
					if (str[i + 1] == '\"')
					{
						// Regard "" as a single "
						tmp[wp++] = '\"';
						i++;
					}
					else
					{
						// Enable the ignoring space flag for a single "
						ignore_space = true;
					}
				}
				else
				{
					tmp[wp++] = c;
				}

				mode = 1;
			}
			break;

		case 1:
			if (ignore_space == false && (c == ' ' || c == '\t'))
			{
				// End of the token
				tmp[wp++] = 0;
				wp = 0;

				Insert(o, CopyStr(tmp));
				mode = 0;
			}
			else
			{
				if (c == '\"')
				{
					if (str[i + 1] == '\"')
					{
						// Regard "" as a single "
						tmp[wp++] = L'\"';
						i++;
					}
					else
					{
						if (ignore_space == false)
						{
							// Enable the ignoring space flag for a single "
							ignore_space = true;
						}
						else
						{
							// Disable the space ignore flag
							ignore_space = false;
						}
					}
				}
				else
				{
					tmp[wp++] = c;
				}
			}
			break;
		}
	}

	if (wp != 0)
	{
		tmp[wp++] = 0;
		Insert(o, CopyStr(tmp));
	}

	Free(tmp);

	t = ZeroMalloc(sizeof(TOKEN_LIST));
	t->NumTokens = LIST_NUM(o);
	t->Token = ZeroMalloc(sizeof(char *) * t->NumTokens);
	for (i = 0;i < t->NumTokens;i++)
	{
		t->Token[i] = LIST_DATA(o, i);
	}

	ReleaseList(o);

	return t;
}