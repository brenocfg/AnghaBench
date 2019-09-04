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
 size_t StrLen (char*) ; 
 char ToLower (char) ; 
 char ToUpper (char) ; 

void SetStrCaseAccordingToBits(char *str, UINT bits)
{
	UINT i, len;
	// Validate arguments
	if (str == NULL)
	{
		return;
	}

	len = StrLen(str);

	for (i = 0;i < len;i++)
	{
		char c = str[i];

		if (bits & 0x01)
		{
			c = ToUpper(c);
		}
		else
		{
			c = ToLower(c);
		}

		str[i] = c;

		bits = bits / 2;
	}
}