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
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_4__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  ConbinePathW (char*,size_t,char*,char*) ; 
 char* CopyUtfToUni (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* GetCurrentPathEnvStr () ; 
 scalar_t__ IsFileExistsInnerW (char*) ; 
 int MAX_SIZE ; 
 TYPE_1__* ParseSplitedPathW (char*) ; 
 int /*<<< orphan*/  UniFreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  UniStrCpy (char*,size_t,char*) ; 
 int UnixCheckExecAccessW (char*) ; 
 int /*<<< orphan*/  UnixGetCurrentDirW (char*,size_t) ; 
 int /*<<< orphan*/  Win32GetCurrentDirW (char*,size_t) ; 

void UnixGetExeNameW(wchar_t *name, UINT size, wchar_t *arg)
{
	UNI_TOKEN_LIST *t;
	char *path_str;
	wchar_t *path_str_w;
	bool ok = false;
	// Validate arguments
	if (name == NULL || arg == NULL)
	{
		return;
	}

	path_str = GetCurrentPathEnvStr();
	path_str_w = CopyUtfToUni(path_str);

	t = ParseSplitedPathW(path_str_w);

	if (t != NULL)
	{
		UINT i;
		for (i = 0;i < t->NumTokens;i++)
		{
			wchar_t *s = t->Token[i];
			wchar_t tmp[MAX_SIZE];

			ConbinePathW(tmp, sizeof(tmp), s, arg);

			if (IsFileExistsInnerW(tmp))
			{
#ifdef	OS_UNIX
				if (UnixCheckExecAccessW(tmp) == false)
				{
					continue;
				}
#endif	// OS_UNIX
				ok = true;
				UniStrCpy(name, size, tmp);
				break;
			}
		}

		UniFreeToken(t);
	}

	Free(path_str);
	Free(path_str_w);

	if (ok == false)
	{
		// In the case of failing to find the path
#ifdef	OS_UNIX
		UnixGetCurrentDirW(name, size);
#else	// OS_UNIX
		Win32GetCurrentDirW(name, size);
#endif	// OS_UNIX
		ConbinePathW(name, size, name, arg);
	}
}