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
struct mapping {struct map_value* values; } ;
struct map_value {int dummy; } ;
struct macro_group {int (* find_builtin ) (char*,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  htab_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct map_value** add_map_value (struct map_value**,int,char const*) ; 
 struct mapping* add_mapping (struct macro_group*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal_expected_char (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  read_name (char*,int /*<<< orphan*/ *) ; 
 int read_skip_spaces (int /*<<< orphan*/ *) ; 
 char* read_string (int /*<<< orphan*/ *,int) ; 
 int stub1 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mapping *
read_mapping (struct macro_group *group, htab_t table, FILE *infile)
{
  char tmp_char[256];
  struct mapping *m;
  struct map_value **end_ptr;
  const char *string;
  int number, c;

  /* Read the mapping name and create a structure for it.  */
  read_name (tmp_char, infile);
  m = add_mapping (group, table, tmp_char, infile);

  c = read_skip_spaces (infile);
  if (c != '[')
    fatal_expected_char (infile, '[', c);

  /* Read each value.  */
  end_ptr = &m->values;
  c = read_skip_spaces (infile);
  do
    {
      if (c != '(')
	{
	  /* A bare symbol name that is implicitly paired to an
	     empty string.  */
	  ungetc (c, infile);
	  read_name (tmp_char, infile);
	  string = "";
	}
      else
	{
	  /* A "(name string)" pair.  */
	  read_name (tmp_char, infile);
	  string = read_string (infile, false);
	  c = read_skip_spaces (infile);
	  if (c != ')')
	    fatal_expected_char (infile, ')', c);
	}
      number = group->find_builtin (tmp_char, infile);
      end_ptr = add_map_value (end_ptr, number, string);
      c = read_skip_spaces (infile);
    }
  while (c != ']');

  c = read_skip_spaces (infile);
  if (c != ')')
    fatal_expected_char (infile, ')', c);

  return m;
}