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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,char*,char*) ; 
 char* hostname ; 
 char* progname ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 char* username ; 

__attribute__((used)) static void
make_banner(FILE *fp)
{
  time_t t = time((time_t *) NULL);
  char *cp = ctime(&t);

  fprintf(fp,
	  "\
# *** This file was automatically generated -- DO NOT EDIT HERE ***\n\
# \"%s\" run by %s@%s on %s\
#\n\
",
	  progname, username, hostname, cp);
}