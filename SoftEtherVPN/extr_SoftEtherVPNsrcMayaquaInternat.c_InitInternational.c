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

/* Variables and functions */

void InitInternational()
{
#ifdef	OS_UNIX
	void *d;

	if (iconv_lock != NULL)
	{
		return;
	}

	GetCurrentCharSet(charset, sizeof(charset));
	d = IconvWideToStrInternal();
	if (d == (void *)-1)
	{
#if defined (UNIX_MACOS) || defined (UNIX_LINUX_MUSL)
		StrCpy(charset, sizeof(charset), "utf-8");
#else // defined (UNIX_MACOS) || defined (UNIX_LINUX_MUSL) 
		StrCpy(charset, sizeof(charset), "EUCJP");
#endif // defined (UNIX_MACOS) || defined (UNIX_LINUX_MUSL) 
		d = IconvWideToStrInternal();
		if (d == (void *)-1)
		{
			StrCpy(charset, sizeof(charset), "US");
		}
		else
		{
			IconvFreeInternal(d);
		}
	}
	else
	{
		IconvFreeInternal(d);
	}

	iconv_lock = NewLockMain();

	iconv_cache_wide_to_str = IconvWideToStrInternal();
	iconv_cache_str_to_wide = IconvStrToWideInternal();
#endif	// OS_UNIX
}