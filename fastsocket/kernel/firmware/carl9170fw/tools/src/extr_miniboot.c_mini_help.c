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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void mini_help(void)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "\tminiboot ACTION FW-FILE [MB-FILE]\n");

	fprintf(stderr, "\nDescription:\n");
	fprintf(stderr, "\tFirmware concatenation utility.\n");

	fprintf(stderr, "\nParameteres:\n");
	fprintf(stderr, "\t'ACTION'	= [a|d]\n");
	fprintf(stderr, "\t | 'a'	= Add miniboot firmware.\n");
	fprintf(stderr, "\t * 'd'	= remove miniboot firmware.\n");
	fprintf(stderr, "\t'FW-FILE'	= destination for the package.\n");
	fprintf(stderr, "\t'MB-FILE'	= extra firmware image.\n");
}