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
 int fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int my_fputs(char *s, FILE *stream)
{
	char *p;

	for (p = s + strlen(s) - 1; p >= s; p--)
		if (!isspace(*p))
			break;
	p++;

	/* use DOS endings for better viewer compatibility */
	memcpy(p, "\r\n", 3);

	return fputs(s, stream);
}