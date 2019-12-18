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
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_line_number ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 

int fgetline(char* buff, int nchars, FILE* file)
{
	int length;

	if(fgets(buff, nchars, file) == NULL)
		return -1;
	if(buff[0] == '\r')
		memcpy(buff, buff + 1, nchars - 1);

	length = strlen(buff);
	while(length && (buff[length-1] == '\r' || buff[length-1] == '\n'))
		length--;
	buff[length] = 0;
	g_line_number++;

	return length;
}