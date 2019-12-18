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

/* Variables and functions */
 int EINVAL ; 
 int strlen (char const*) ; 

int fdfs_validate_filename(const char *filename)
{
	const char *p;
	const char *pEnd;
	int len;

	len = strlen(filename);
	pEnd = filename + len;
	for (p=filename; p<pEnd; p++)
	{
		if (!((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') || \
			(*p >= '0' && *p <= '9') || (*p == '-') || (*p == '_')\
			|| (*p == '.')))
		{
			return EINVAL;
		}
	}

	return 0;
}