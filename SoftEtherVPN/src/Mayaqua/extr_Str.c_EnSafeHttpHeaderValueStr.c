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
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Move (char*,char*,size_t) ; 
 size_t StrLen (char*) ; 

void EnSafeHttpHeaderValueStr(char *str, char replace)
{
	UINT length = 0;
	UINT index = 0;

	// Validate arguments
	if (str == NULL)
	{
		return;
	}

	length = StrLen(str);
	while (index < length)
	{
		if (str[index] == '\r' || str[index] == '\n')
		{
			if (replace == ' ')
			{
				Move(&str[index], &str[index + 1], length - index);
			}
			else
			{
				str[index] = replace;
			}
		}
		else if (str[index] == '\\')
		{
			if (str[index + 1] == 'r' || str[index + 1] == 'n')
			{
				if (replace == ' ')
				{
					Move(&str[index], &str[index + 2], length - index);
					index--;
				}
				else
				{
					str[index] = str[index + 1] = replace;
					index++;
				}
			}
		}
		index++;
	}
}