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
struct TYPE_4__ {char** Token; int NumTokens; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 void* Malloc (int) ; 
 int /*<<< orphan*/  UniStrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 int UniStrLen (char*) ; 
 TYPE_1__* UnixUniParseToken (char*,char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 void* ZeroMalloc (int) ; 
 int /*<<< orphan*/  token_lock ; 
 char* wcstok (char*,char*,char**) ; 

UNI_TOKEN_LIST *UniParseToken(wchar_t *src, wchar_t *separator)
{
#ifdef	OS_WIN32
	UNI_TOKEN_LIST *ret;
	wchar_t *tmp;
	wchar_t *str1, *str2;
	UINT len, num;

#if	(!defined _MSC_VER) || (_MSC_VER >= 1900)
	wchar_t *state = NULL;
#endif	// (!defined _MSC_VER) || (_MSC_VER >= 1900)

	// Validate arguments
	if (src == NULL)
	{
		ret = ZeroMalloc(sizeof(UNI_TOKEN_LIST));
		ret->Token = ZeroMalloc(0);
		return ret;
	}
	if (separator == NULL)
	{
		separator = L" .\t\r\n";
	}
	len = UniStrLen(src);
	str1 = Malloc((len + 1) * sizeof(wchar_t));
	str2 = Malloc((len + 1) * sizeof(wchar_t));
	UniStrCpy(str1, 0, src);
	UniStrCpy(str2, 0, src);

	Lock(token_lock);
	{
		tmp = wcstok(str1, separator
#if	(!defined _MSC_VER) || (_MSC_VER >= 1900)
			, &state
#endif	// (!defined _MSC_VER) || (_MSC_VER >= 1900)
			);
		num = 0;
		while (tmp != NULL)
		{
			num++;
			tmp = wcstok(NULL, separator
#if	(!defined _MSC_VER) || (_MSC_VER >= 1900)
				, &state
#endif	// (!defined _MSC_VER) || (_MSC_VER >= 1900)
				);
		}
		ret = Malloc(sizeof(UNI_TOKEN_LIST));
		ret->NumTokens = num;
		ret->Token = (wchar_t **)Malloc(sizeof(wchar_t *) * num);
		num = 0;
		tmp = wcstok(str2, separator
#if	(!defined _MSC_VER) || (_MSC_VER >= 1900)
			, &state
#endif	// (!defined _MSC_VER) || (_MSC_VER >= 1900)
			);
		while (tmp != NULL)
		{
			ret->Token[num] = (wchar_t *)Malloc((UniStrLen(tmp) + 1) * sizeof(wchar_t));
			UniStrCpy(ret->Token[num], 0, tmp);
			num++;
			tmp = wcstok(NULL, separator
#if	(!defined _MSC_VER) || (_MSC_VER >= 1900)
				, &state
#endif	// (!defined _MSC_VER) || (_MSC_VER >= 1900)
				);
		}
	}
	Unlock(token_lock);

	Free(str1);
	Free(str2);
	return ret;
#else	// OS_WIN32
	return UnixUniParseToken(src, separator);
#endif	// OS_WIN32
}