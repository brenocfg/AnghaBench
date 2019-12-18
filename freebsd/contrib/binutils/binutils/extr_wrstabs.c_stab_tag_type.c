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
struct stab_write_handle {int dummy; } ;
typedef  enum debug_type_kind { ____Placeholder_debug_type_kind } debug_type_kind ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 long stab_get_struct_index (struct stab_write_handle*,char const*,unsigned int,int,unsigned int*) ; 
 int /*<<< orphan*/  stab_push_defined_type (struct stab_write_handle*,long,unsigned int) ; 

__attribute__((used)) static bfd_boolean
stab_tag_type (void *p, const char *name, unsigned int id,
	       enum debug_type_kind kind)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;
  long index;
  unsigned int size = 0;

  index = stab_get_struct_index (info, name, id, kind, &size);
  if (index < 0)
    return FALSE;

  return stab_push_defined_type (info, index, size);
}