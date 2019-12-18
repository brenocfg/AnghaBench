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
 char FourBitToHex (int) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 int StrLen (char*) ; 

void ToHex(char *str, UINT value)
{
	char tmp[MAX_SIZE];
	UINT wp = 0;
	UINT len, i;
	// Validate arguments
	if (str == NULL)
	{
		return;
	}

	// Set to empty character
	StrCpy(tmp, 0, "");

	// Append from the last digit
	while (true)
	{
		UINT a = (UINT)(value % (UINT)16);
		value = value / (UINT)16;
		tmp[wp++] = FourBitToHex(a);
		if (value == 0)
		{
			tmp[wp++] = 0;
			break;
		}
	}

	// Reverse order
	len = StrLen(tmp);
	for (i = 0;i < len;i++)
	{
		str[len - i - 1] = tmp[i];
	}
	str[len] = 0;
}