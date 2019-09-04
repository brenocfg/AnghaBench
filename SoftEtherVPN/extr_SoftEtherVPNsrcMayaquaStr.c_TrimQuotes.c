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
 int /*<<< orphan*/  Move (char*,char*,int) ; 
 int StrLen (char*) ; 

void TrimQuotes(char *str)
{
	UINT len = 0;
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

	if (str[len - 1] == '\"')
	{
		str[len - 1] = 0;
	}

	if (str[0] == '\"')
	{
		Move(str, str + 1, len);
	}
}