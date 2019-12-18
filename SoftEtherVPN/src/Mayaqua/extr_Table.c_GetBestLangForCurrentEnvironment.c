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
typedef  int /*<<< orphan*/  lang ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  LANGLIST ;

/* Variables and functions */
 int /*<<< orphan*/ * GetBestLangByLangStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * GetBestLangByLcid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetEnv (char*,char*,int) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MsGetUserLocaleId () ; 

LANGLIST *GetBestLangForCurrentEnvironment(LIST *o)
{
	LANGLIST *ret = NULL;
	// Validate arguments
	if (o == NULL)
	{
		return NULL;
	}

#ifdef	OS_WIN32
	ret = GetBestLangByLcid(o, MsGetUserLocaleId());
#else	// OS_WIN32
	if (true)
	{
		char lang[MAX_SIZE];

		if (GetEnv("LANG", lang, sizeof(lang)))
		{
			ret = GetBestLangByLangStr(o, lang);
		}
		else
		{
			ret = GetBestLangByLangStr(o, "C");
		}
	}
#endif	// OS_WIN32

	return ret;
}