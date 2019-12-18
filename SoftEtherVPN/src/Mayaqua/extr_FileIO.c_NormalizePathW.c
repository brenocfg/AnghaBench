#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  cd ;
struct TYPE_9__ {size_t NumTokens; int** Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  size_t UINT ;
struct TYPE_10__ {int num_item; scalar_t__* p; } ;
typedef  TYPE_2__ SK ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertPathW (int*) ; 
 int /*<<< orphan*/  GetHomeDirW (int*,int) ; 
 int MAX_SIZE ; 
 TYPE_2__* NewSk () ; 
 int /*<<< orphan*/  Pop (TYPE_2__*) ; 
 int /*<<< orphan*/  Push (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  ReleaseSk (TYPE_2__*) ; 
 int /*<<< orphan*/  UniFreeToken (TYPE_1__*) ; 
 TYPE_1__* UniParseToken (int*,char*) ; 
 scalar_t__ UniStartWith (int*,char*) ; 
 int /*<<< orphan*/  UniStrCat (int*,int,...) ; 
 scalar_t__ UniStrCmpi (int*,char*) ; 
 int /*<<< orphan*/  UniStrCpy (int*,size_t,...) ; 
 int UniStrLen (int*) ; 
 int /*<<< orphan*/  UniTrim (int*) ; 
 int /*<<< orphan*/  UnixGetCurrentDirW (int*,int) ; 
 int /*<<< orphan*/  Win32GetCurrentDirW (int*,int) ; 
 int /*<<< orphan*/  Zero (int*,int) ; 

void NormalizePathW(wchar_t *dst, UINT size, wchar_t *src)
{
	wchar_t tmp[MAX_SIZE];
	UNI_TOKEN_LIST *t;
	bool first_double_slash = false;
	bool first_single_slash = false;
#ifdef  OS_WIN32
	wchar_t win32_drive_char = 0;
#endif  // OS_WIN32
	bool is_full_path = false;
	UINT i;
	SK *sk;
	// Validate arguments
	if (dst == NULL || src == 0)
	{
		return;
	}

	// Convert the path (Win32, UNIX conversion)
	UniStrCpy(tmp, sizeof(tmp), src);
	ConvertPathW(tmp);
	UniTrim(tmp);

	// If the path begins with "./ " or " ../", replace it to the current directory
	if (UniStartWith(tmp, L"./") || UniStartWith(tmp, L".\\") ||
		UniStartWith(tmp, L"../") || UniStartWith(tmp, L"..\\") ||
		UniStrCmpi(tmp, L".") == 0 || UniStrCmpi(tmp, L"..") == 0)
	{
		wchar_t cd[MAX_SIZE];
		Zero(cd, sizeof(cd));

#ifdef	OS_WIN32
		Win32GetCurrentDirW(cd, sizeof(cd));
#else	// OS_WIN32
		UnixGetCurrentDirW(cd, sizeof(cd));
#endif	// OS_WIN32

		if (UniStartWith(tmp, L".."))
		{
			UniStrCat(cd, sizeof(cd), L"/../");
			UniStrCat(cd, sizeof(cd), tmp + 2);
		}
		else
		{
			UniStrCat(cd, sizeof(cd), L"/");
			UniStrCat(cd, sizeof(cd), tmp);
		}

		UniStrCpy(tmp, sizeof(tmp), cd);
	}

	// If the path starts with "~/", replace it with the home directory
	if (UniStartWith(tmp, L"~/") || UniStartWith(tmp, L"~\\"))
	{
		wchar_t tmp2[MAX_SIZE];
		GetHomeDirW(tmp2, sizeof(tmp2));
		UniStrCat(tmp2, sizeof(tmp2), L"/");
		UniStrCat(tmp2, sizeof(tmp2), tmp + 2);
		UniStrCpy(tmp, sizeof(tmp), tmp2);
	}

	if (UniStartWith(tmp, L"//") || UniStartWith(tmp, L"\\\\"))
	{
        // Begin with "//" or "\\"
		first_double_slash = true;
		is_full_path = true;
	}
	else if (UniStartWith(tmp, L"/") || UniStartWith(tmp, L"\\"))
	{
		// Begin with "\"
		first_single_slash = true;
		is_full_path = true;
	}

#ifdef	OS_WIN32
	if (UniStrLen(tmp) >= 2)
	{
		if (tmp[1] == L':')
		{
			// The drive string representation of the Win32
			wchar_t tmp2[MAX_SIZE];
			is_full_path = true;
			win32_drive_char = tmp[0];
			UniStrCpy(tmp2, sizeof(tmp2), tmp + 2);
			UniStrCpy(tmp, sizeof(tmp), tmp2);
		}
	}
#endif	// OS_WIN32

	if (UniStrLen(tmp) == 1 && (tmp[0] == L'/' || tmp[0] == L'\\'))
	{
		tmp[0] = 0;
	}

	// Tokenize
	t = UniParseToken(tmp, L"/\\");

	sk = NewSk();

	for (i = 0;i < t->NumTokens;i++)
	{
		wchar_t *s = t->Token[i];

		if (UniStrCmpi(s, L".") == 0)
		{
			continue;
		}
		else if (UniStrCmpi(s, L"..") == 0)
		{
			if (sk->num_item >= 1 && (first_double_slash == false || sk->num_item >= 2))
			{
				Pop(sk);
			}
		}
		else
		{
			Push(sk, s);
		}
	}

	// Token concatenation
	UniStrCpy(tmp, sizeof(tmp), L"");

	if (first_double_slash)
	{
		UniStrCat(tmp, sizeof(tmp), L"//");
	}
	else if (first_single_slash)
	{
		UniStrCat(tmp, sizeof(tmp), L"/");
	}

#ifdef  OS_WIN32
	if (win32_drive_char != 0)
	{
		wchar_t d[2];
		d[0] = win32_drive_char;
		d[1] = 0;
		UniStrCat(tmp, sizeof(tmp), d);
		UniStrCat(tmp, sizeof(tmp), L":/");
	}
#endif  // OS_WIN32

	for (i = 0;i < sk->num_item;i++)
	{
		UniStrCat(tmp, sizeof(tmp), (wchar_t *)sk->p[i]);
		if (i != (sk->num_item - 1))
		{
			UniStrCat(tmp, sizeof(tmp), L"/");
		}
	}

	ReleaseSk(sk);

	UniFreeToken(t);

	ConvertPathW(tmp);

	UniStrCpy(dst, size, tmp);
}