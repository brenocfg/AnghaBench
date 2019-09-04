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
 int /*<<< orphan*/  StrCat (char*,size_t,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,size_t,char*) ; 
 size_t StrLen (char*) ; 

void GetOmissionName(char *dst, UINT size, char *src)
{
	UINT i, len;
	// Validate arguments
	if (dst == NULL || src == NULL)
	{
		return;
	}

	StrCpy(dst, size, "");
	len = StrLen(src);

	for (i = 0;i < len;i++)
	{
		char c = src[i];

		if ((c >= '0' && c <= '9') ||
			(c >= 'A' && c <= 'Z'))
		{
			char tmp[2];
			tmp[0] = c;
			tmp[1] = 0;

			StrCat(dst, size, tmp);
		}
	}
}