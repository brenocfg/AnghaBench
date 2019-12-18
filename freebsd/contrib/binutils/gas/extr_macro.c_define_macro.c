#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ len; char* ptr; } ;
typedef  TYPE_1__ sb ;
struct TYPE_21__ {char* file; unsigned int line; char* name; TYPE_1__ sub; int /*<<< orphan*/  formal_hash; scalar_t__ formals; scalar_t__ formal_count; } ;
typedef  TYPE_2__ macro_entry ;
typedef  int /*<<< orphan*/  PTR ;

/* Variables and functions */
 char TOLOWER (char) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  buffer_and_nest (char*,char*,TYPE_1__*,int (*) (TYPE_1__*)) ; 
 int do_formals (TYPE_2__*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  free_macro (TYPE_2__*) ; 
 int get_token (int,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ hash_find (int /*<<< orphan*/ ,char*) ; 
 char* hash_jam (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_new () ; 
 int macro_defined ; 
 int /*<<< orphan*/  macro_hash ; 
 int /*<<< orphan*/  sb_add_sb (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  sb_new (TYPE_1__*) ; 
 int sb_skip_comma (int,TYPE_1__*) ; 
 int sb_skip_white (int,TYPE_1__*) ; 
 void* sb_terminate (TYPE_1__*) ; 
 scalar_t__ xmalloc (int) ; 

const char *
define_macro (int idx, sb *in, sb *label,
	      int (*get_line) (sb *),
	      char *file, unsigned int line,
	      const char **namep)
{
  macro_entry *macro;
  sb name;
  const char *error = NULL;

  macro = (macro_entry *) xmalloc (sizeof (macro_entry));
  sb_new (&macro->sub);
  sb_new (&name);
  macro->file = file;
  macro->line = line;

  macro->formal_count = 0;
  macro->formals = 0;
  macro->formal_hash = hash_new ();

  idx = sb_skip_white (idx, in);
  if (! buffer_and_nest ("MACRO", "ENDM", &macro->sub, get_line))
    error = _("unexpected end of file in macro `%s' definition");
  if (label != NULL && label->len != 0)
    {
      sb_add_sb (&name, label);
      macro->name = sb_terminate (&name);
      if (idx < in->len && in->ptr[idx] == '(')
	{
	  /* It's the label: MACRO (formals,...)  sort  */
	  idx = do_formals (macro, idx + 1, in);
	  if (idx < in->len && in->ptr[idx] == ')')
	    idx = sb_skip_white (idx + 1, in);
	  else if (!error)
	    error = _("missing `)' after formals in macro definition `%s'");
	}
      else
	{
	  /* It's the label: MACRO formals,...  sort  */
	  idx = do_formals (macro, idx, in);
	}
    }
  else
    {
      int cidx;

      idx = get_token (idx, in, &name);
      macro->name = sb_terminate (&name);
      if (name.len == 0)
	error = _("Missing macro name");
      cidx = sb_skip_white (idx, in);
      idx = sb_skip_comma (cidx, in);
      if (idx == cidx || idx < in->len)
	idx = do_formals (macro, idx, in);
      else
	idx = cidx;
    }
  if (!error && idx < in->len)
    error = _("Bad parameter list for macro `%s'");

  /* And stick it in the macro hash table.  */
  for (idx = 0; idx < name.len; idx++)
    name.ptr[idx] = TOLOWER (name.ptr[idx]);
  if (hash_find (macro_hash, macro->name))
    error = _("Macro `%s' was already defined");
  if (!error)
    error = hash_jam (macro_hash, macro->name, (PTR) macro);

  if (namep != NULL)
    *namep = macro->name;

  if (!error)
    macro_defined = 1;
  else
    free_macro (macro);

  return error;
}