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
struct TYPE_2__ {int /*<<< orphan*/ * methods; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static bfd_boolean
stab_class_end_method (void *p)
{
  struct stab_write_handle *info = (struct stab_write_handle *) p;

  assert (info->type_stack != NULL && info->type_stack->methods != NULL);

  /* We allocated enough room on info->type_stack->methods to add the
     trailing semicolon.  */
  strcat (info->type_stack->methods, ";");

  return TRUE;
}