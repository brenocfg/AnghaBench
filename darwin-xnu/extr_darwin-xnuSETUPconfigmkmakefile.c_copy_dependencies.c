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
 int /*<<< orphan*/  LINESIZE ; 
 int /*<<< orphan*/  OLDSALUTATION ; 
 int /*<<< orphan*/ * fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 char* makbuf ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 

void
copy_dependencies(FILE *makin, FILE *makout)
{
	int oldlen = (sizeof OLDSALUTATION - 1);

	while (fgets(makbuf, LINESIZE, makin) != NULL) {
		if (! strncmp(makbuf, OLDSALUTATION, oldlen))
			break;
	}
	while (fgets(makbuf, LINESIZE, makin) != NULL) {
		if (oldlen != 0)
		{
			if (makbuf[0] == '\n')
				continue;
			else
				oldlen = 0;
		}
		fputs(makbuf, makout);
	}
}