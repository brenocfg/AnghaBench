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
typedef  int /*<<< orphan*/  tmp ;
typedef  size_t UINT ;

/* Variables and functions */
 scalar_t__ EndWith (char*,char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  NormalizePath (char*,size_t,char*) ; 
 int /*<<< orphan*/  StrCat (char*,size_t,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,size_t,char*) ; 
 int StrLen (char*) ; 

void GetDirNameFromFilePath(char *dst, UINT size, char *filepath)
{
	char tmp[MAX_SIZE];
	UINT wp;
	UINT i;
	UINT len;
	// Validate arguments
	if (dst == NULL || filepath == NULL)
	{
		return;
	}

	StrCpy(tmp, sizeof(tmp), filepath);
	if (EndWith(tmp, "\\") || EndWith(tmp, "/"))
	{
		tmp[StrLen(tmp) - 1] = 0;
	}

	len = StrLen(tmp);

	StrCpy(dst, size, "");

	wp = 0;

	for (i = 0;i < len;i++)
	{
		char c = tmp[i];
		if (c == '/' || c == '\\')
		{
			tmp[wp++] = 0;
			wp = 0;
			StrCat(dst, size, tmp);
			tmp[wp++] = c;
		}
		else
		{
			tmp[wp++] = c;
		}
	}

	if (StrLen(dst) == 0)
	{
		StrCpy(dst, size, "/");
	}

	NormalizePath(dst, size, dst);
}