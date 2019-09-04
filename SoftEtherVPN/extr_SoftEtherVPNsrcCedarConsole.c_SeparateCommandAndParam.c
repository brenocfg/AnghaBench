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
typedef  int wchar_t ;
typedef  int UINT ;

/* Variables and functions */
 int* CopyUniStr (int*) ; 
 char* CopyUniToStr (int*) ; 
 int /*<<< orphan*/  Free (int*) ; 
 int* Malloc (int) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int* UniCopyStr (int*) ; 
 int /*<<< orphan*/  UniIsEmptyStr (int*) ; 
 int UniStrLen (int*) ; 
 int /*<<< orphan*/  UniTrim (int*) ; 
 int /*<<< orphan*/  UniTrimCrlf (int*) ; 

bool SeparateCommandAndParam(wchar_t *src, char **cmd, wchar_t **param)
{
	UINT i, len, wp;
	wchar_t *tmp;
	wchar_t *src_tmp;
	// Validate arguments
	if (src == NULL)
	{
		return false;
	}
	if (cmd != NULL)
	{
		*cmd = NULL;
	}
	if (param != NULL)
	{
		*param = NULL;
	}

	src_tmp = UniCopyStr(src);
	UniTrimCrlf(src_tmp);
	UniTrim(src_tmp);

	len = UniStrLen(src_tmp);
	tmp = Malloc(sizeof(wchar_t) * (len + 32));
	wp = 0;

	for (i = 0;i < (len + 1);i++)
	{
		wchar_t c = src_tmp[i];

		switch (c)
		{
		case 0:
		case L' ':
		case L'\t':
			tmp[wp] = 0;
			if (UniIsEmptyStr(tmp))
			{
				Free(tmp);
				Free(src_tmp);
				return false;
			}
			if (cmd != NULL)
			{
				*cmd = CopyUniToStr(tmp);
				Trim(*cmd);
			}
			goto ESCAPE;

		default:
			tmp[wp++] = c;
			break;
		}
	}

ESCAPE:
	if (param != NULL)
	{
		*param = CopyUniStr(&src_tmp[wp]);
		UniTrim(*param);
	}

	Free(tmp);
	Free(src_tmp);

	return true;
}