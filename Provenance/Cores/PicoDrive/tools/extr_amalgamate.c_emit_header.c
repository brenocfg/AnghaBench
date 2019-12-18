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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void emit_header(FILE *f, const char *fname)
{
	char tmp[128] = "/*                                                            */";
	memcpy(tmp + 3, fname, strlen(fname));
	fprintf(f, "\n\n");
	fprintf(f, "/**************************************************************/\n");
	fprintf(f, "/**************************************************************/\n");
	fprintf(f, "%s\n", tmp);
	fprintf(f, "/**************************************************************/\n");
}