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
 int /*<<< orphan*/  FOPEN_RT ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,int /*<<< orphan*/ ) ; 
 int itbl_have_entries ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int
itbl_parse (char *insntbl)
{
  extern FILE *yyin;
  extern int yyparse (void);

  yyin = fopen (insntbl, FOPEN_RT);
  if (yyin == 0)
    {
      printf ("Can't open processor instruction specification file \"%s\"\n",
	      insntbl);
      return 1;
    }

  while (yyparse ())
    ;

  fclose (yyin);
  itbl_have_entries = 1;
  return 0;
}