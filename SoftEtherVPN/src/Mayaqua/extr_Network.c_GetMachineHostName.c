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
 int /*<<< orphan*/  ConvertSafeFileName (char*,size_t,char*) ; 
 int /*<<< orphan*/  GetMachineName (char*,int) ; 
 int MAX_SIZE ; 
 size_t StrLen (char*) ; 

void GetMachineHostName(char *name, UINT size)
{
	char tmp[MAX_SIZE];
	UINT i, len;
	// Validate arguments
	if (name == NULL)
	{
		return;
	}

	GetMachineName(tmp, sizeof(tmp));

	len = StrLen(tmp);
	for (i = 0;i < len;i++)
	{
		if (tmp[i] == '.')
		{
			tmp[i] = 0;
		}
	}

	ConvertSafeFileName(name, size, tmp);
}