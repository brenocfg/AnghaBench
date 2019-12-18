#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {char const* ptr_name; int stub_p; int used; int /*<<< orphan*/  symbol; } ;
typedef  TYPE_1__ machopic_indirection ;

/* Variables and functions */
 char* IDENTIFIER_POINTER (scalar_t__) ; 
 scalar_t__ IDENTIFIER_TRANSPARENT_ALIAS (scalar_t__) ; 
 int /*<<< orphan*/  INSERT ; 
 char* NON_LAZY_POINTER_SUFFIX ; 
 char* STUB_SUFFIX ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 char* XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* alloca (int) ; 
 scalar_t__ ggc_alloc (int) ; 
 scalar_t__ htab_create_ggc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void** htab_find_slot_with_hash (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_string (char*) ; 
 int /*<<< orphan*/  machopic_indirection_eq ; 
 int /*<<< orphan*/  machopic_indirection_hash ; 
 scalar_t__ machopic_indirections ; 
 scalar_t__ maybe_get_identifier (char const*) ; 
 int name_needs_quotes (char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*,char const*,char const*,char const*) ; 
 int strlen (char const*) ; 
 char* user_label_prefix ; 
 char const* xstrdup (char*) ; 

const char *
machopic_indirection_name (rtx sym_ref, bool stub_p)
{
  char *buffer;
  const char *name = XSTR (sym_ref, 0);
  size_t namelen = strlen (name);
  machopic_indirection *p;
  void ** slot;
  bool saw_star = false;
  bool needs_quotes;
  const char *suffix;
  const char *prefix = user_label_prefix;
  const char *quote = "";
  tree id;

  id = maybe_get_identifier (name);
  if (id)
    {
      tree id_orig = id;

      while (IDENTIFIER_TRANSPARENT_ALIAS (id))
	id = TREE_CHAIN (id);
      if (id != id_orig)
	{
	  name = IDENTIFIER_POINTER (id);
	  namelen = strlen (name);
	}
    }

  if (name[0] == '*')
    {
      saw_star = true;
      prefix = "";
      ++name;
      --namelen;
    }

  needs_quotes = name_needs_quotes (name);
  if (needs_quotes)
    {
      quote = "\"";
    }

  if (stub_p)
    suffix = STUB_SUFFIX;
  else
    suffix = NON_LAZY_POINTER_SUFFIX;

  buffer = alloca (strlen ("&L")
		   + strlen (prefix)
		   + namelen
		   + strlen (suffix)
		   + 2 * strlen (quote)
		   + 1 /* '\0' */);

  /* Construct the name of the non-lazy pointer or stub.  */
  sprintf (buffer, "&%sL%s%s%s%s", quote, prefix, name, suffix, quote);

  if (!machopic_indirections)
    machopic_indirections = htab_create_ggc (37,
					     machopic_indirection_hash,
					     machopic_indirection_eq,
					     /*htab_del=*/NULL);

  slot = htab_find_slot_with_hash (machopic_indirections, buffer,
				   htab_hash_string (buffer), INSERT);
  if (*slot)
    {
      p = (machopic_indirection *) *slot;
    }
  else
    {
      p = (machopic_indirection *) ggc_alloc (sizeof (machopic_indirection));
      p->symbol = sym_ref;
      p->ptr_name = xstrdup (buffer);
      p->stub_p = stub_p;
      p->used = false;
      *slot = p;
    }

  return p->ptr_name;
}