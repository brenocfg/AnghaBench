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
 char* DOCBOOK ; 
 char* FUNCTION ; 
 char* KERNELDOC ; 
 int /*<<< orphan*/  exec_kernel_doc (char**) ; 

__attribute__((used)) static void docsect(char *filename, char *line)
{
	char *vec[6]; /* kerneldoc -docbook -function "section" file NULL */
	char *s;

	for (s = line; *s; s++)
		if (*s == '\n')
			*s = '\0';

	vec[0] = KERNELDOC;
	vec[1] = DOCBOOK;
	vec[2] = FUNCTION;
	vec[3] = line;
	vec[4] = filename;
	vec[5] = NULL;
	exec_kernel_doc(vec);
}