#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* string; } ;
struct ieee_name_type_hash_entry {struct ieee_name_type* types; TYPE_1__ root; } ;
struct ieee_buflist {int dummy; } ;
struct TYPE_5__ {scalar_t__ localp; char* name; scalar_t__ ignorep; struct ieee_buflist strdef; int /*<<< orphan*/  indx; } ;
struct ieee_name_type {unsigned int id; scalar_t__ kind; TYPE_2__ type; struct ieee_name_type* next; } ;
struct ieee_handle {TYPE_3__* type_stack; int /*<<< orphan*/  type_indx; int /*<<< orphan*/  tags; } ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_6__ {TYPE_2__ type; } ;

/* Variables and functions */
 scalar_t__ DEBUG_KIND_ILLEGAL ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ieee_define_named_type (struct ieee_handle*,char const*,int /*<<< orphan*/ ,unsigned int,scalar_t__,scalar_t__,struct ieee_buflist*) ; 
 int /*<<< orphan*/  ieee_init_buffer (struct ieee_handle*,struct ieee_buflist*) ; 
 struct ieee_name_type_hash_entry* ieee_name_type_hash_lookup (int /*<<< orphan*/ *,char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ieee_write_number (struct ieee_handle*,unsigned int) ; 
 int /*<<< orphan*/  memset (struct ieee_name_type*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static bfd_boolean
ieee_start_struct_type (void *p, const char *tag, unsigned int id,
			bfd_boolean structp, unsigned int size)
{
  struct ieee_handle *info = (struct ieee_handle *) p;
  bfd_boolean localp, ignorep;
  bfd_boolean copy;
  char ab[20];
  const char *look;
  struct ieee_name_type_hash_entry *h;
  struct ieee_name_type *nt, *ntlook;
  struct ieee_buflist strdef;

  localp = FALSE;
  ignorep = FALSE;

  /* We need to create a tag for internal use even if we don't want
     one for external use.  This will let us refer to an anonymous
     struct.  */
  if (tag != NULL)
    {
      look = tag;
      copy = FALSE;
    }
  else
    {
      sprintf (ab, "__anon%u", id);
      look = ab;
      copy = TRUE;
    }

  /* If we already have references to the tag, we must use the
     existing type index.  */
  h = ieee_name_type_hash_lookup (&info->tags, look, TRUE, copy);
  if (h == NULL)
    return FALSE;

  nt = NULL;
  for (ntlook = h->types; ntlook != NULL; ntlook = ntlook->next)
    {
      if (ntlook->id == id)
	nt = ntlook;
      else if (! ntlook->type.localp)
	{
	  /* We are creating a duplicate definition of a globally
	     defined tag.  Force it to be local to avoid
	     confusion.  */
	  localp = TRUE;
	}
    }

  if (nt != NULL)
    {
      assert (localp == nt->type.localp);
      if (nt->kind == DEBUG_KIND_ILLEGAL && ! localp)
	{
	  /* We've already seen a global definition of the type.
             Ignore this new definition.  */
	  ignorep = TRUE;
	}
    }
  else
    {
      nt = (struct ieee_name_type *) xmalloc (sizeof *nt);
      memset (nt, 0, sizeof *nt);
      nt->id = id;
      nt->type.name = h->root.string;
      nt->next = h->types;
      h->types = nt;
      nt->type.indx = info->type_indx;
      ++info->type_indx;
    }

  nt->kind = DEBUG_KIND_ILLEGAL;

  if (! ieee_init_buffer (info, &strdef)
      || ! ieee_define_named_type (info, tag, nt->type.indx, size, TRUE,
				   localp, &strdef)
      || ! ieee_write_number (info, structp ? 'S' : 'U')
      || ! ieee_write_number (info, size))
    return FALSE;

  if (! ignorep)
    {
      const char *hold;

      /* We never want nt->type.name to be NULL.  We want the rest of
	 the type to be the object set up on the type stack; it will
	 have a NULL name if tag is NULL.  */
      hold = nt->type.name;
      nt->type = info->type_stack->type;
      nt->type.name = hold;
    }

  info->type_stack->type.name = tag;
  info->type_stack->type.strdef = strdef;
  info->type_stack->type.ignorep = ignorep;

  return TRUE;
}