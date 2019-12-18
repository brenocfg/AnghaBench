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
struct ieee_modified_type {unsigned int pointer; } ;
struct ieee_handle {TYPE_2__* type_stack; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {unsigned int indx; int /*<<< orphan*/  localp; } ;
struct TYPE_4__ {TYPE_1__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ieee_define_type (struct ieee_handle*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee_modified_type* ieee_get_modified_info (void*,unsigned int) ; 
 unsigned int ieee_pop_type (struct ieee_handle*) ; 
 int /*<<< orphan*/  ieee_push_type (struct ieee_handle*,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_write_number (struct ieee_handle*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
ieee_pointer_type (void *p)
{
  struct ieee_handle *info = (struct ieee_handle *) p;
  bfd_boolean localp;
  unsigned int indx;
  struct ieee_modified_type *m = NULL;

  localp = info->type_stack->type.localp;
  indx = ieee_pop_type (info);

  /* A pointer to a simple builtin type can be obtained by adding 32.
     FIXME: Will this be a short pointer, and will that matter?  */
  if (indx < 32)
    return ieee_push_type (info, indx + 32, 0, TRUE, FALSE);

  if (! localp)
    {
      m = ieee_get_modified_info (p, indx);
      if (m == NULL)
	return FALSE;

      /* FIXME: The size should depend upon the architecture.  */
      if (m->pointer > 0)
	return ieee_push_type (info, m->pointer, 4, TRUE, FALSE);
    }

  if (! ieee_define_type (info, 4, TRUE, localp)
      || ! ieee_write_number (info, 'P')
      || ! ieee_write_number (info, indx))
    return FALSE;

  if (! localp)
    m->pointer = info->type_stack->type.indx;

  return TRUE;
}