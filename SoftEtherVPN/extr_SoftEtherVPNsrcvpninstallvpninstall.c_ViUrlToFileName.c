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
 int lstrlen (char*) ; 

char *ViUrlToFileName(char *url)
{
	UINT i, len;
	char *ret = url;
	bool b = true;
	len = lstrlen(url);

	for (i = 0;i < len;i++)
	{
		char c = url[i];

		if (c == '?' || c == '#')
		{
			b = false;
		}

		if (b)
		{
			if (c == '/' || c == '\\')
			{
				if (lstrlen(url + i + 1) > 1)
				{
					ret = url + i + 1;
				}
			}
		}
	}

	return ret;
}