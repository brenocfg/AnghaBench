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
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  CopyStrToUni (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CopyUniToStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CopyUtfToUni (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/  ReplaceStrEx (char*,int,char*,char*,char*,int) ; 
 scalar_t__ SearchStrEx (char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetCommandLineStr (char*) ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 char* ZeroMalloc (int) ; 
 int /*<<< orphan*/  exename ; 
 int /*<<< orphan*/  exename_w ; 

void InitCommandLineStr(int argc, char **argv)
{
	if (argc >= 1)
	{
#ifdef	OS_UNIX
		exename_w = CopyUtfToUni(argv[0]);
		exename = CopyUniToStr(exename_w);
#else	// OS_UNIX
		exename = CopyStr(argv[0]);
		exename_w = CopyStrToUni(exename);
#endif	// OS_UNIX
	}
	if (argc < 2 || argv == NULL)
	{
		// No command-line string
		SetCommandLineStr(NULL);
	}
	else
	{
		// There are command-line string
		int i, total_len = 1;
		char *tmp;

		for (i = 1;i < argc;i++)
		{
			total_len += StrLen(argv[i]) * 2 + 32;
		}
		tmp = ZeroMalloc(total_len);

		for (i = 1;i < argc;i++)
		{
			UINT s_size = StrLen(argv[i]) * 2;
			char *s = ZeroMalloc(s_size);
			bool dq = (SearchStrEx(argv[i], " ", 0, true) != INFINITE);
			ReplaceStrEx(s, s_size, argv[i], "\"", "\"\"", true);
			if (dq)
			{
				StrCat(tmp, total_len, "\"");
			}
			StrCat(tmp, total_len, s);
			if (dq)
			{
				StrCat(tmp, total_len, "\"");
			}
			StrCat(tmp, total_len, " ");
			Free(s);
		}

		Trim(tmp);
		SetCommandLineStr(tmp);
		Free(tmp);
	}
}