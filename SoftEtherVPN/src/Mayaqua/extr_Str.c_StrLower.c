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

void StrLower(char *str)
{
	UINT len, i;
	// Validate arguments
	if (str == NULL)
	{
		return;
	}

	len = StrLen(str);
	for (i = 0;i < len;i++)
	{
		str[i] = ToLower(str[i]);
	}
}