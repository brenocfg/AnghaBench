#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee_modified_type {scalar_t__ const_qualified; } ;
struct ieee_handle {TYPE_2__* type_stack; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {unsigned int size; scalar_t__ indx; int /*<<< orphan*/  localp; int /*<<< orphan*/  unsignedp; } ;
struct TYPE_4__ {TYPE_1__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ieee_define_type (struct ieee_handle*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee_modified_type* ieee_get_modified_info (struct ieee_handle*,unsigned int) ; 
 unsigned int ieee_pop_type (struct ieee_handle*) ; 
 int /*<<< orphan*/  ieee_push_type (struct ieee_handle*,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_write_number (struct ieee_handle*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
ieee_const_type (void *p)
{
  struct ieee_handle *info = (struct ieee_handle *) p;
  unsigned int size;
  bfd_boolean unsignedp, localp;
  unsigned int indx;
  struct ieee_modified_type *m = NULL;

  size = info->type_stack->type.size;
  unsignedp = info->type_stack->type.unsignedp;
  localp = info->type_stack->type.localp;
  indx = ieee_pop_type (info);

  if (! localp)
    {
      m = ieee_get_modified_info (info, indx);
      if (m == NULL)
	return FALSE;

      if (m->const_qualified > 0)
	return ieee_push_type (info, m->const_qualified, size, unsignedp,
			       FALSE);
    }

  if (! ieee_define_type (info, size, unsignedp, localp)
      || ! ieee_write_number (info, 'n')
      || ! ieee_write_number (info, 1)
      || ! ieee_write_number (info, indx))
    return FALSE;

  if (! localp)
    m->const_qualified = info->type_stack->type.indx;

  return TRUE;
}