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
struct stab_write_handle {TYPE_1__* type_stack; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  stab_modify_type (struct stab_write_handle*,char,int /*<<< orphan*/ ,long**,size_t*) ; 

__attribute__((used)) static bfd_boolean
stab_const_type (void *p)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;

  return stab_modify_type (info, 'k', info->type_stack->size,
			   (long **) NULL, (size_t *) NULL);
}