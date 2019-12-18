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
struct TYPE_2__ {scalar_t__ void_type; } ;
struct stab_write_handle {long type_index; TYPE_1__ type_cache; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sprintf (char*,char*,long,long) ; 
 int /*<<< orphan*/  stab_push_defined_type (struct stab_write_handle*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stab_push_string (struct stab_write_handle*,char*,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
stab_void_type (void *p)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;

  if (info->type_cache.void_type != 0)
    return stab_push_defined_type (info, info->type_cache.void_type, 0);
  else
    {
      long index;
      char buf[40];

      index = info->type_index;
      ++info->type_index;

      info->type_cache.void_type = index;

      sprintf (buf, "%ld=%ld", index, index);

      return stab_push_string (info, buf, index, TRUE, 0);
    }
}