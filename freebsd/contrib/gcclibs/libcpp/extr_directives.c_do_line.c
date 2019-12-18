#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
struct line_maps {int used; struct line_map* maps; } ;
struct line_map {unsigned char sysp; char* to_file; } ;
struct TYPE_19__ {int /*<<< orphan*/  len; int /*<<< orphan*/  text; } ;
struct TYPE_20__ {TYPE_10__ str; } ;
struct TYPE_21__ {scalar_t__ type; TYPE_1__ val; } ;
typedef  TYPE_2__ cpp_token ;
struct TYPE_22__ {scalar_t__ text; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ cpp_string ;
struct TYPE_23__ {struct line_maps* line_table; } ;
typedef  TYPE_4__ cpp_reader ;

/* Variables and functions */
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 int /*<<< orphan*/  CPP_DL_PEDWARN ; 
 scalar_t__ CPP_EOF ; 
 scalar_t__ CPP_NUMBER ; 
 scalar_t__ CPP_OPTION (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ CPP_PEDANTIC (TYPE_4__*) ; 
 scalar_t__ CPP_STRING ; 
 int /*<<< orphan*/  LC_RENAME ; 
 int /*<<< orphan*/  _cpp_do_file_change (TYPE_4__*,int /*<<< orphan*/ ,char const*,unsigned long,unsigned char) ; 
 int /*<<< orphan*/  c99 ; 
 int /*<<< orphan*/  check_eol (TYPE_4__*) ; 
 int /*<<< orphan*/  cpp_error (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* cpp_get_token (TYPE_4__*) ; 
 scalar_t__ cpp_interpret_string_notranslate (TYPE_4__*,TYPE_10__*,int,TYPE_3__*,int) ; 
 int /*<<< orphan*/  cpp_token_as_text (TYPE_4__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  skip_rest_of_line (TYPE_4__*) ; 
 scalar_t__ strtoul_for_line (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static void
do_line (cpp_reader *pfile)
{
  const struct line_maps *line_table = pfile->line_table;
  const struct line_map *map = &line_table->maps[line_table->used - 1];

  /* skip_rest_of_line() may cause line table to be realloc()ed so note down
     sysp right now.  */

  unsigned char map_sysp = map->sysp;
  const cpp_token *token;
  const char *new_file = map->to_file;
  unsigned long new_lineno;

  /* C99 raised the minimum limit on #line numbers.  */
  unsigned int cap = CPP_OPTION (pfile, c99) ? 2147483647 : 32767;

  /* #line commands expand macros.  */
  token = cpp_get_token (pfile);
  if (token->type != CPP_NUMBER
      || strtoul_for_line (token->val.str.text, token->val.str.len,
			   &new_lineno))
    {
      cpp_error (pfile, CPP_DL_ERROR,
		 "\"%s\" after #line is not a positive integer",
		 cpp_token_as_text (pfile, token));
      return;
    }

  if (CPP_PEDANTIC (pfile) && (new_lineno == 0 || new_lineno > cap))
    cpp_error (pfile, CPP_DL_PEDWARN, "line number out of range");

  token = cpp_get_token (pfile);
  if (token->type == CPP_STRING)
    {
      cpp_string s = { 0, 0 };
      if (cpp_interpret_string_notranslate (pfile, &token->val.str, 1,
					    &s, false))
	new_file = (const char *)s.text;
      check_eol (pfile);
    }
  else if (token->type != CPP_EOF)
    {
      cpp_error (pfile, CPP_DL_ERROR, "\"%s\" is not a valid filename",
		 cpp_token_as_text (pfile, token));
      return;
    }

  skip_rest_of_line (pfile);
  _cpp_do_file_change (pfile, LC_RENAME, new_file, new_lineno,
		       map_sysp);
}