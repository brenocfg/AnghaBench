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
struct TYPE_2__ {int /*<<< orphan*/  reference_types_alloc; int /*<<< orphan*/  reference_types; } ;
struct stab_write_handle {TYPE_1__ type_cache; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  stab_modify_type (struct stab_write_handle*,char,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
stab_reference_type (void *p)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;

  /* FIXME: The size should depend upon the architecture.  */
  return stab_modify_type (info, '&', 4, &info->type_cache.reference_types,
			   &info->type_cache.reference_types_alloc);
}