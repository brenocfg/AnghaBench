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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,float) ; 
 int strlen (char*) ; 

int WriteFloat(FILE *fp, float value)
{
	char buf[128];
	int l;

	sprintf(buf, "%f", value);
	l = strlen(buf);
	//strip any trailing zeros
	while(l-- > 1)
	{
		if (buf[l] != '0' && buf[l] != '.') break;
		if (buf[l] == '.')
		{
			buf[l] = 0;
			break;
		} //end if
		buf[l] = 0;
	} //end while
	//write the float to file
	if (fprintf(fp, "%s", buf) < 0) return 0;
	return 1;
}