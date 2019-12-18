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
struct hash_control {int dummy; } ;
struct alias {char const* name; int /*<<< orphan*/  line; int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/  PTR ;

/* Variables and functions */
 int /*<<< orphan*/  SKIP_WHITESPACE () ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct hash_control* alias_hash ; 
 struct hash_control* alias_name_hash ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  as_fatal (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  as_where (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* demand_copy_C_string (int*) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 
 char get_symbol_end () ; 
 scalar_t__ hash_find (struct hash_control*,char*) ; 
 char* hash_jam (struct hash_control*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_canonicalize_symbol_name (char*) ; 
 int /*<<< orphan*/  ignore_rest_of_line () ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  notes ; 
 char* obstack_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  obstack_grow (int /*<<< orphan*/ *,char*,int) ; 
 struct hash_control* secalias_hash ; 
 struct hash_control* secalias_name_hash ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
dot_alias (int section)
{
  char *name, *alias;
  char delim;
  char *end_name;
  int len;
  const char *error_string;
  struct alias *h;
  const char *a;
  struct hash_control *ahash, *nhash;
  const char *kind;

  name = input_line_pointer;
  delim = get_symbol_end ();
  end_name = input_line_pointer;
  *end_name = delim;

  if (name == end_name)
    {
      as_bad (_("expected symbol name"));
      ignore_rest_of_line ();
      return;
    }

  SKIP_WHITESPACE ();

  if (*input_line_pointer != ',')
    {
      *end_name = 0;
      as_bad (_("expected comma after \"%s\""), name);
      *end_name = delim;
      ignore_rest_of_line ();
      return;
    }

  input_line_pointer++;
  *end_name = 0;
  ia64_canonicalize_symbol_name (name);

  /* We call demand_copy_C_string to check if alias string is valid.
     There should be a closing `"' and no `\0' in the string.  */
  alias = demand_copy_C_string (&len);
  if (alias == NULL)
    {
      ignore_rest_of_line ();
      return;
    }

  /* Make a copy of name string.  */
  len = strlen (name) + 1;
  obstack_grow (&notes, name, len);
  name = obstack_finish (&notes);

  if (section)
    {
      kind = "section";
      ahash = secalias_hash;
      nhash = secalias_name_hash;
    }
  else
    {
      kind = "symbol";
      ahash = alias_hash;
      nhash = alias_name_hash;
    }

  /* Check if alias has been used before.  */
  h = (struct alias *) hash_find (ahash, alias);
  if (h)
    {
      if (strcmp (h->name, name))
	as_bad (_("`%s' is already the alias of %s `%s'"),
		alias, kind, h->name);
      goto out;
    }

  /* Check if name already has an alias.  */
  a = (const char *) hash_find (nhash, name);
  if (a)
    {
      if (strcmp (a, alias))
	as_bad (_("%s `%s' already has an alias `%s'"), kind, name, a);
      goto out;
    }

  h = (struct alias *) xmalloc (sizeof (struct alias));
  as_where (&h->file, &h->line);
  h->name = name;
  
  error_string = hash_jam (ahash, alias, (PTR) h);
  if (error_string)
    {
      as_fatal (_("inserting \"%s\" into %s alias hash table failed: %s"),
		alias, kind, error_string);
      goto out;
    }

  error_string = hash_jam (nhash, name, (PTR) alias);
  if (error_string)
    {
      as_fatal (_("inserting \"%s\" into %s name hash table failed: %s"),
		alias, kind, error_string);
out:
      obstack_free (&notes, name);
      obstack_free (&notes, alias);
    }

  demand_empty_rest_of_line ();
}