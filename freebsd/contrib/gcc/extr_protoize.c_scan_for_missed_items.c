#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* hash_entry; TYPE_3__* defs_decs; } ;
typedef  TYPE_2__ file_info ;
struct TYPE_7__ {int const line; scalar_t__ is_func_def; struct TYPE_7__* next_in_file; } ;
typedef  TYPE_3__ def_dec_info ;
struct TYPE_5__ {int /*<<< orphan*/  symbol; } ;

/* Variables and functions */
 scalar_t__ ISALPHA (unsigned char const) ; 
 scalar_t__ ISSPACE (unsigned char const) ; 
 char* alloca (size_t) ; 
 char* careful_find_l_paren (char const*) ; 
 int /*<<< orphan*/  check_source (int,char const*) ; 
 char* clean_text_base ; 
 char* clean_text_limit ; 
 int identify_lineno (char const*) ; 
 scalar_t__ is_id_char (char const) ; 
 int /*<<< orphan*/  notice (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pname ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shortpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  source_confusion_recovery ; 
 int /*<<< orphan*/  strcmp (char*,char const* const) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static void
scan_for_missed_items (const file_info *file_p)
{
  static const char *scan_p;
  const char *limit = clean_text_limit - 3;
  static const char *backup_limit;

  backup_limit = clean_text_base - 1;

  for (scan_p = clean_text_base; scan_p < limit; scan_p++)
    {
      if (*scan_p == ')')
	{
	  static const char *last_r_paren;
	  const char *ahead_p;

	  last_r_paren = scan_p;

	  for (ahead_p = scan_p + 1; ISSPACE ((const unsigned char)*ahead_p); )
	    check_source (++ahead_p < limit, limit);

	  scan_p = ahead_p - 1;

	  if (ISALPHA ((const unsigned char)*ahead_p) || *ahead_p == '{')
	    {
	      const char *last_l_paren;
	      const int lineno = identify_lineno (ahead_p);

	      if (setjmp (source_confusion_recovery))
		continue;

	      /* We know we have a function definition header.  Now skip
	         leftwards over all of its associated formals lists.  */

	      do
		{
		  last_l_paren = careful_find_l_paren (last_r_paren);
		  for (last_r_paren = last_l_paren-1;
		       ISSPACE ((const unsigned char)*last_r_paren); )
		    check_source (--last_r_paren >= backup_limit, backup_limit);
		}
	      while (*last_r_paren == ')');

	      if (is_id_char (*last_r_paren))
		{
		  const char *id_limit = last_r_paren + 1;
		  const char *id_start;
		  size_t id_length;
		  const def_dec_info *dd_p;

		  for (id_start = id_limit-1; is_id_char (*id_start); )
		    check_source (--id_start >= backup_limit, backup_limit);
		  id_start++;
		  backup_limit = id_start;
		  if ((id_length = (size_t) (id_limit - id_start)) == 0)
		    goto not_missed;

		  {
		    char *func_name = alloca (id_length + 1);
		    static const char * const stmt_keywords[]
		      = { "if", "else", "do", "while", "for", "switch", "case", "return", 0 };
		    const char * const *stmt_keyword;

		    strncpy (func_name, id_start, id_length);
		    func_name[id_length] = '\0';

		    /* We must check here to see if we are actually looking at
		       a statement rather than an actual function call.  */

		    for (stmt_keyword = stmt_keywords; *stmt_keyword; stmt_keyword++)
		      if (!strcmp (func_name, *stmt_keyword))
			goto not_missed;

#if 0
		    notice ("%s: found definition of '%s' at %s(%d)\n",
			    pname,
			    func_name,
			    shortpath (NULL, file_p->hash_entry->symbol),
			    identify_lineno (id_start));
#endif				/* 0 */
		    /* We really should check for a match of the function name
		       here also, but why bother.  */

		    for (dd_p = file_p->defs_decs; dd_p; dd_p = dd_p->next_in_file)
		      if (dd_p->is_func_def && dd_p->line == lineno)
			goto not_missed;

		    /* If we make it here, then we did not know about this
		       function definition.  */

		    notice ("%s: %d: warning: '%s' excluded by preprocessing\n",
			    shortpath (NULL, file_p->hash_entry->symbol),
			    identify_lineno (id_start), func_name);
		    notice ("%s: function definition not converted\n",
			    pname);
		  }
		not_missed: ;
	        }
	    }
	}
    }
}