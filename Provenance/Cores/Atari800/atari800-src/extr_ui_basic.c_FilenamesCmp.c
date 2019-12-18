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
 int Util_stricmp (char const*,char const*) ; 

__attribute__((used)) static int FilenamesCmp(const char *filename1, const char *filename2)
{
	if (filename1[0] == '[') {
		if (filename2[0] != '[')
			return -1;
		if (filename1[1] == '.') {
			if (filename2[1] != '.')
				return -1;
			/* return Util_stricmp(filename1, filename2); */
		}
		else if (filename2[1] == '.')
			return 1;
		/* return Util_stricmp(filename1, filename2); */
	}
	else if (filename2[0] == '[')
		return 1;
	return Util_stricmp(filename1, filename2);
}