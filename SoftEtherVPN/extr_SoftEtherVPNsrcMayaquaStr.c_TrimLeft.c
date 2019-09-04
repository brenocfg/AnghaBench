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
typedef  scalar_t__ UINT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  Free (char*) ; 
 char* Malloc (scalar_t__) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ StrLen (char*) ; 
 scalar_t__ TRUE ; 

void TrimLeft(char *str)
{
	char *buf;
	UINT len, i, wp;
	BOOL flag;
	// Validate arguments
	if (str == NULL)
	{
		return;
	}
	len = StrLen(str);
	if (len == 0)
	{
		return;
	}
	if (str[0] != ' ' && str[0] != '\t')
	{
		return;
	}

	buf = Malloc(len + 1);
	flag = FALSE;
	wp = 0;
	for (i = 0;i < len;i++)
	{
		if (str[i] != ' ' && str[i] != '\t')
		{
			flag = TRUE;
		}
		if (flag)
		{
			buf[wp++] = str[i];
		}
	}
	buf[wp] = 0;
	StrCpy(str, 0, buf);
	Free(buf);
}