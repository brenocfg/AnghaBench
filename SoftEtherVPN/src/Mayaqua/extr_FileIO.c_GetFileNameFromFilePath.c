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
 int MAX_SIZE ; 
 size_t MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  StrCpy (char*,size_t,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 

void GetFileNameFromFilePath(char *dst, UINT size, char *filepath)
{
	char tmp[MAX_SIZE];
	UINT i, len, wp;
	// Validate arguments
	if (dst == NULL || filepath == NULL)
	{
		return;
	}

	len = MIN(StrLen(filepath), (MAX_SIZE - 2));
	wp = 0;

	for (i = 0;i < (len + 1);i++)
	{
		char c = filepath[i];

		switch (c)
		{
		case '\\':
		case '/':
		case 0:
			tmp[wp] = 0;
			wp = 0;
			break;

		default:
			tmp[wp] = c;
			wp++;
			break;
		}
	}

	StrCpy(dst, size, tmp);
}