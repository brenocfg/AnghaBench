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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ CONST ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 char TOUPPER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 char* XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 char* scan_comma_elt (char const**) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  write_upcase (char*) ; 

__attribute__((used)) static void
gen_attr (rtx attr)
{
  const char *p, *tag;
  int is_const = GET_CODE (XEXP (attr, 2)) == CONST;

  printf ("#define HAVE_ATTR_%s\n", XSTR (attr, 0));

  /* If numeric attribute, don't need to write an enum.  */
  p = XSTR (attr, 1);
  if (*p == '\0')
    printf ("extern int get_attr_%s (%s);\n", XSTR (attr, 0),
	    (is_const ? "void" : "rtx"));
  else
    {
      printf ("enum attr_%s {", XSTR (attr, 0));

      while ((tag = scan_comma_elt (&p)) != 0)
	{
	  write_upcase (XSTR (attr, 0));
	  putchar ('_');
	  while (tag != p)
	    putchar (TOUPPER (*tag++));
	  if (*p == ',')
	    fputs (", ", stdout);
	}

      fputs ("};\n", stdout);
      printf ("extern enum attr_%s get_attr_%s (%s);\n\n",
	      XSTR (attr, 0), XSTR (attr, 0), (is_const ? "void" : "rtx"));
    }

  /* If `length' attribute, write additional function definitions and define
     variables used by `insn_current_length'.  */
  if (! strcmp (XSTR (attr, 0), "length"))
    {
      puts ("\
extern void shorten_branches (rtx);\n\
extern int insn_default_length (rtx);\n\
extern int insn_min_length (rtx);\n\
extern int insn_variable_length_p (rtx);\n\
extern int insn_current_length (rtx);\n\n\
#include \"insn-addr.h\"\n");
    }
}