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
struct stab_write_handle {long type_index; TYPE_1__* type_stack; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {long index; int /*<<< orphan*/  definition; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memset (long*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long,...) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 int /*<<< orphan*/  stab_push_defined_type (struct stab_write_handle*,long,unsigned int) ; 
 int /*<<< orphan*/  stab_push_string (struct stab_write_handle*,char*,long,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ xmalloc (scalar_t__) ; 
 scalar_t__ xrealloc (long*,size_t) ; 

__attribute__((used)) static bfd_boolean
stab_modify_type (struct stab_write_handle *info, int mod,
		  unsigned int size, long **cache, size_t *cache_alloc)
{
  long targindex;
  long index;
  char *s, *buf;

  assert (info->type_stack != NULL);
  targindex = info->type_stack->index;

  if (targindex <= 0
      || cache == NULL)
    {
      bfd_boolean definition;

      /* Either the target type has no index, or we aren't caching
         this modifier.  Either way we have no way of recording the
         new type, so we don't bother to define one.  */
      definition = info->type_stack->definition;
      s = stab_pop_type (info);
      buf = (char *) xmalloc (strlen (s) + 2);
      sprintf (buf, "%c%s", mod, s);
      free (s);
      if (! stab_push_string (info, buf, 0, definition, size))
	return FALSE;
      free (buf);
    }
  else
    {
      if ((size_t) targindex >= *cache_alloc)
	{
	  size_t alloc;

	  alloc = *cache_alloc;
	  if (alloc == 0)
	    alloc = 10;
	  while ((size_t) targindex >= alloc)
	    alloc *= 2;
	  *cache = (long *) xrealloc (*cache, alloc * sizeof (long));
	  memset (*cache + *cache_alloc, 0,
		  (alloc - *cache_alloc) * sizeof (long));
	  *cache_alloc = alloc;
	}

      index = (*cache)[targindex];
      if (index != 0 && ! info->type_stack->definition)
	{
	  /* We have already defined a modification of this type, and
             the entry on the type stack is not a definition, so we
             can safely discard it (we may have a definition on the
             stack, even if we already defined a modification, if it
             is a struct which we did not define at the time it was
             referenced).  */
	  free (stab_pop_type (info));
	  if (! stab_push_defined_type (info, index, size))
	    return FALSE;
	}
      else
	{
	  index = info->type_index;
	  ++info->type_index;

	  s = stab_pop_type (info);
	  buf = (char *) xmalloc (strlen (s) + 20);
	  sprintf (buf, "%ld=%c%s", index, mod, s);
	  free (s);

	  (*cache)[targindex] = index;

	  if (! stab_push_string (info, buf, index, TRUE, size))
	    return FALSE;

	  free (buf);
	}
    }

  return TRUE;
}