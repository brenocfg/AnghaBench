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
struct TYPE_2__ {scalar_t__* float_types; } ;
struct stab_write_handle {long type_index; TYPE_1__ type_cache; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long,char*,unsigned int) ; 
 int /*<<< orphan*/  stab_int_type (struct stab_write_handle*,int,int /*<<< orphan*/ ) ; 
 char* stab_pop_type (struct stab_write_handle*) ; 
 int /*<<< orphan*/  stab_push_defined_type (struct stab_write_handle*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  stab_push_string (struct stab_write_handle*,char*,long,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static bfd_boolean
stab_float_type (void *p, unsigned int size)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;

  if (size > 0
      && size - 1 < (sizeof info->type_cache.float_types
		     / sizeof info->type_cache.float_types[0])
      && info->type_cache.float_types[size - 1] != 0)
    return stab_push_defined_type (info,
				   info->type_cache.float_types[size - 1],
				   size);
  else
    {
      long index;
      char *int_type;
      char buf[50];

      /* Floats are defined as a subrange of int.  */
      if (! stab_int_type (info, 4, FALSE))
	return FALSE;
      int_type = stab_pop_type (info);

      index = info->type_index;
      ++info->type_index;

      if (size > 0
	  && size - 1 < (sizeof info->type_cache.float_types
			 / sizeof info->type_cache.float_types[0]))
	info->type_cache.float_types[size - 1] = index;

      sprintf (buf, "%ld=r%s;%u;0;", index, int_type, size);

      free (int_type);

      return stab_push_string (info, buf, index, TRUE, size);
    }
}