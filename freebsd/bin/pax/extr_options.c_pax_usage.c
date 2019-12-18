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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
pax_usage(void)
{
	(void)fputs("usage: pax [-cdnOvz] [-E limit] [-f archive] ", stderr);
	(void)fputs("[-s replstr] ... [-U user] ...", stderr);
	(void)fputs("\n	   [-G group] ... ", stderr);
	(void)fputs("[-T [from_date][,to_date]] ... ", stderr);
	(void)fputs("[pattern ...]\n", stderr);
	(void)fputs("       pax -r [-cdiknOuvzDYZ] [-E limit] ", stderr);
	(void)fputs("[-f archive] [-o options] ... \n", stderr);
	(void)fputs("	   [-p string] ... [-s replstr] ... ", stderr);
	(void)fputs("[-U user] ... [-G group] ...\n	   ", stderr);
	(void)fputs("[-T [from_date][,to_date]] ... ", stderr);
	(void)fputs(" [pattern ...]\n", stderr);
	(void)fputs("       pax -w [-dituvzHLOPX] [-b blocksize] ", stderr);
	(void)fputs("[ [-a] [-f archive] ] [-x format] \n", stderr);
	(void)fputs("	   [-B bytes] [-s replstr] ... ", stderr);
	(void)fputs("[-o options] ... [-U user] ...", stderr);
	(void)fputs("\n	   [-G group] ... ", stderr);
	(void)fputs("[-T [from_date][,to_date][/[c][m]]] ... ", stderr);
	(void)fputs("[file ...]\n", stderr);
	(void)fputs("       pax -r -w [-diklntuvDHLOPXYZ] ", stderr);
	(void)fputs("[-p string] ... [-s replstr] ...", stderr);
	(void)fputs("\n	   [-U user] ... [-G group] ... ", stderr);
	(void)fputs("[-T [from_date][,to_date][/[c][m]]] ... ", stderr);
	(void)fputs("\n	   [file ...] directory\n", stderr);
	exit(1);
}