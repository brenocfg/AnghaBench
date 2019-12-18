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
struct string_hash_entry {long index; unsigned int size; } ;
struct stab_write_handle {long type_index; int /*<<< orphan*/  typedef_hash; TYPE_1__* type_stack; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {long index; unsigned int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  N_LSYM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,...) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 int /*<<< orphan*/  stab_write_symbol (struct stab_write_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 struct string_hash_entry* string_hash_lookup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

__attribute__((used)) static bfd_boolean
stab_typdef (void *p, const char *name)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  long index;
  unsigned int size;
  char *s, *buf;
  struct string_hash_entry *h;

  index = info->type_stack->index;
  size = info->type_stack->size;
  s = stab_pop_type (info);

  buf = (char *) xmalloc (strlen (name) + strlen (s) + 20);

  if (index > 0)
    sprintf (buf, "%s:t%s", name, s);
  else
    {
      index = info->type_index;
      ++info->type_index;
      sprintf (buf, "%s:t%ld=%s", name, index, s);
    }

  free (s);

  if (! stab_write_symbol (info, N_LSYM, 0, 0, buf))
    return FALSE;

  free (buf);

  h = string_hash_lookup (&info->typedef_hash, name, TRUE, FALSE);
  if (h == NULL)
    {
      non_fatal (_("string_hash_lookup failed: %s"),
		 bfd_errmsg (bfd_get_error ()));
      return FALSE;
    }

  /* I don't think we care about redefinitions.  */

  h->index = index;
  h->size = size;

  return TRUE;
}