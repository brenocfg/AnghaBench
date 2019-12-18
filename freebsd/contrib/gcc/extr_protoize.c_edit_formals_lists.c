#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  formals_list; struct TYPE_10__* chain_next; } ;
typedef  TYPE_4__ f_list_chain_item ;
struct TYPE_11__ {TYPE_4__* f_list_chain; int /*<<< orphan*/  formal_names; TYPE_3__* file; TYPE_1__* hash_entry; } ;
typedef  TYPE_5__ def_dec_info ;
struct TYPE_9__ {TYPE_2__* hash_entry; } ;
struct TYPE_8__ {int /*<<< orphan*/  symbol; } ;
struct TYPE_7__ {char* symbol; } ;

/* Variables and functions */
 scalar_t__ ISSPACE (unsigned char const) ; 
 int /*<<< orphan*/  check_source (int,char const*) ; 
 char const* clean_read_ptr ; 
 int /*<<< orphan*/  dupnstr (char const*,size_t) ; 
 int /*<<< orphan*/  identify_lineno (char const*) ; 
 scalar_t__ is_id_char (char const) ; 
 int /*<<< orphan*/  notice (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  output_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_up_to (char const*) ; 
 int /*<<< orphan*/  shortpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 

__attribute__((used)) static int
edit_formals_lists (const char *end_formals, unsigned int f_list_count,
		    const def_dec_info *def_dec_p)
{
  const char *start_formals;
  int depth;

  start_formals = end_formals - 1;
  depth = 1;
  for (; depth; check_source (--start_formals > clean_read_ptr, 0))
    {
      switch (*start_formals)
	{
	case '(':
	  depth--;
	  break;
	case ')':
	  depth++;
	  break;
	}
    }
  start_formals++;

  /* start_formals now points to the opening left paren of the formals list.  */

  f_list_count--;

  if (f_list_count)
    {
      const char *next_end;

      /* There should be more formal lists to the left of here.  */

      next_end = start_formals - 1;
      check_source (next_end > clean_read_ptr, 0);
      while (ISSPACE ((const unsigned char)*next_end))
	check_source (--next_end > clean_read_ptr, 0);
      check_source (*next_end == ')', next_end);
      check_source (--next_end > clean_read_ptr, 0);
      check_source (*next_end == ')', next_end);
      if (edit_formals_lists (next_end, f_list_count, def_dec_p))
	return 1;
    }

  /* Check that the function name in the header we are working on is the same
     as the one we would expect to find.  If not, issue a warning and return
     nonzero.  */

  if (f_list_count == 0)
    {
      const char *expected = def_dec_p->hash_entry->symbol;
      const char *func_name_start;
      const char *func_name_limit;
      size_t func_name_len;

      for (func_name_limit = start_formals-1;
	   ISSPACE ((const unsigned char)*func_name_limit); )
	check_source (--func_name_limit > clean_read_ptr, 0);

      for (func_name_start = func_name_limit++;
	   is_id_char (*func_name_start);
	   func_name_start--)
	check_source (func_name_start > clean_read_ptr, 0);
      func_name_start++;
      func_name_len = func_name_limit - func_name_start;
      if (func_name_len == 0)
	check_source (0, func_name_start);
      if (func_name_len != strlen (expected)
	  || strncmp (func_name_start, expected, func_name_len))
	{
	  notice ("%s: %d: warning: found '%s' but expected '%s'\n",
		  shortpath (NULL, def_dec_p->file->hash_entry->symbol),
		  identify_lineno (func_name_start),
		  dupnstr (func_name_start, func_name_len),
		  expected);
	  return 1;
	}
    }

  output_up_to (start_formals);

#ifdef UNPROTOIZE
  if (f_list_count == 0)
    output_string (def_dec_p->formal_names);
#else /* !defined (UNPROTOIZE) */
  {
    unsigned f_list_depth;
    const f_list_chain_item *flci_p = def_dec_p->f_list_chain;

    /* At this point, the current value of f_list count says how many
       links we have to follow through the f_list_chain to get to the
       particular formals list that we need to output next.  */

    for (f_list_depth = 0; f_list_depth < f_list_count; f_list_depth++)
      flci_p = flci_p->chain_next;
    output_string (flci_p->formals_list);
  }
#endif /* !defined (UNPROTOIZE) */

  clean_read_ptr = end_formals - 1;
  return 0;
}