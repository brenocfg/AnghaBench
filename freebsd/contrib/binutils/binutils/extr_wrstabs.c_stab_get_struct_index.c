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
struct TYPE_2__ {unsigned int struct_types_alloc; struct stab_tag* struct_types; } ;
struct stab_write_handle {scalar_t__ type_index; TYPE_1__ type_cache; } ;
struct stab_tag {scalar_t__ index; char const* tag; int kind; unsigned int size; } ;
typedef  enum debug_type_kind { ____Placeholder_debug_type_kind } debug_type_kind ;

/* Variables and functions */
 int DEBUG_KIND_ILLEGAL ; 
 int /*<<< orphan*/  memset (struct stab_tag*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ xrealloc (struct stab_tag*,size_t) ; 

__attribute__((used)) static long
stab_get_struct_index (struct stab_write_handle *info, const char *tag,
		       unsigned int id, enum debug_type_kind kind,
		       unsigned int *psize)
{
  if (id >= info->type_cache.struct_types_alloc)
    {
      size_t alloc;

      alloc = info->type_cache.struct_types_alloc;
      if (alloc == 0)
	alloc = 10;
      while (id >= alloc)
	alloc *= 2;
      info->type_cache.struct_types =
	(struct stab_tag *) xrealloc (info->type_cache.struct_types,
				      alloc * sizeof (struct stab_tag));
      memset ((info->type_cache.struct_types
	       + info->type_cache.struct_types_alloc),
	      0,
	      ((alloc - info->type_cache.struct_types_alloc)
	       * sizeof (struct stab_tag)));
      info->type_cache.struct_types_alloc = alloc;
    }

  if (info->type_cache.struct_types[id].index == 0)
    {
      info->type_cache.struct_types[id].index = info->type_index;
      ++info->type_index;
      info->type_cache.struct_types[id].tag = tag;
      info->type_cache.struct_types[id].kind = kind;
    }

  if (kind == DEBUG_KIND_ILLEGAL)
    {
      /* This is a definition of the struct.  */
      info->type_cache.struct_types[id].kind = kind;
      info->type_cache.struct_types[id].size = *psize;
    }
  else
    *psize = info->type_cache.struct_types[id].size;

  return info->type_cache.struct_types[id].index;
}