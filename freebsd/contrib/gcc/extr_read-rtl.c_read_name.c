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
struct md_constant {char* name; char* value; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  fatal_with_file_and_line (int /*<<< orphan*/ *,char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ htab_find (scalar_t__,struct md_constant*) ; 
 scalar_t__ md_constants ; 
 int /*<<< orphan*/  read_rtx_lineno ; 
 int read_skip_spaces (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
read_name (char *str, FILE *infile)
{
  char *p;
  int c;

  c = read_skip_spaces (infile);

  p = str;
  while (1)
    {
      if (c == ' ' || c == '\n' || c == '\t' || c == '\f' || c == '\r' || c == EOF)
	break;
      if (c == ':' || c == ')' || c == ']' || c == '"' || c == '/'
	  || c == '(' || c == '[')
	{
	  ungetc (c, infile);
	  break;
	}
      *p++ = c;
      c = getc (infile);
    }
  if (p == str)
    fatal_with_file_and_line (infile, "missing name or number");
  if (c == '\n')
    read_rtx_lineno++;

  *p = 0;

  if (md_constants)
    {
      /* Do constant expansion.  */
      struct md_constant *def;

      p = str;
      do
	{
	  struct md_constant tmp_def;

	  tmp_def.name = p;
	  def = (struct md_constant *) htab_find (md_constants, &tmp_def);
	  if (def)
	    p = def->value;
	} while (def);
      if (p != str)
	strcpy (str, p);
    }
}