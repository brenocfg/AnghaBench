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
struct stab_tag {char* name; scalar_t__ kind; scalar_t__ type; scalar_t__ slot; struct stab_tag* next; } ;
struct stab_handle {struct stab_tag* tags; } ;
typedef  enum debug_type_kind { ____Placeholder_debug_type_kind } debug_type_kind ;
typedef  scalar_t__ debug_type ;

/* Variables and functions */
 scalar_t__ DEBUG_KIND_ILLEGAL ; 
 scalar_t__ DEBUG_TYPE_NULL ; 
 scalar_t__ debug_find_tagged_type (void*,char*,scalar_t__) ; 
 scalar_t__ debug_make_indirect_type (void*,scalar_t__*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memset (struct stab_tag*,int /*<<< orphan*/ ,int) ; 
 char* savestring (char const*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static debug_type
stab_find_tagged_type (void *dhandle, struct stab_handle *info,
		       const char *p, int len, enum debug_type_kind kind)
{
  char *name;
  debug_type dtype;
  struct stab_tag *st;

  name = savestring (p, len);

  /* We pass DEBUG_KIND_ILLEGAL because we want all tags in the same
     namespace.  This is right for C, and I don't know how to handle
     other languages.  FIXME.  */
  dtype = debug_find_tagged_type (dhandle, name, DEBUG_KIND_ILLEGAL);
  if (dtype != DEBUG_TYPE_NULL)
    {
      free (name);
      return dtype;
    }

  /* We need to allocate an entry on the undefined tag list.  */
  for (st = info->tags; st != NULL; st = st->next)
    {
      if (st->name[0] == name[0]
	  && strcmp (st->name, name) == 0)
	{
	  if (st->kind == DEBUG_KIND_ILLEGAL)
	    st->kind = kind;
	  free (name);
	  break;
	}
    }
  if (st == NULL)
    {
      st = (struct stab_tag *) xmalloc (sizeof *st);
      memset (st, 0, sizeof *st);

      st->next = info->tags;
      st->name = name;
      st->kind = kind;
      st->slot = DEBUG_TYPE_NULL;
      st->type = debug_make_indirect_type (dhandle, &st->slot, name);
      info->tags = st;
    }

  return st->type;
}