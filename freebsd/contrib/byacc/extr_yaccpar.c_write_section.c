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
 int /*<<< orphan*/ * code_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  outline ; 

void
write_section(FILE * fp, const char *const section[])
{
    int i;
    const char *s;

    for (i = 0; (s = section[i]) != 0; ++i)
    {
	if (fp == code_file)
	    ++outline;
	fprintf(fp, "%s\n", s);
    }
}