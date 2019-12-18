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
struct ieee_buflist {int dummy; } ;
struct ieee_handle {char* modname; TYPE_2__* type_stack; struct ieee_buflist types; struct ieee_buflist global_types; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {struct ieee_buflist strdef; int /*<<< orphan*/  localp; scalar_t__ ignorep; } ;
struct TYPE_4__ {TYPE_1__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ieee_append_buffer (struct ieee_handle*,struct ieee_buflist*,struct ieee_buflist*) ; 
 scalar_t__ ieee_bb_record_enum ; 
 scalar_t__ ieee_buffer_emptyp (struct ieee_buflist*) ; 
 int /*<<< orphan*/  ieee_change_buffer (struct ieee_handle*,struct ieee_buflist*) ; 
 int /*<<< orphan*/  ieee_init_buffer (struct ieee_handle*,struct ieee_buflist*) ; 
 int /*<<< orphan*/  ieee_write_byte (struct ieee_handle*,int) ; 
 int /*<<< orphan*/  ieee_write_id (struct ieee_handle*,char*) ; 
 int /*<<< orphan*/  ieee_write_number (struct ieee_handle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
ieee_end_struct_type (void *p)
{
  struct ieee_handle *info = (struct ieee_handle *) p;
  struct ieee_buflist *pb;

  assert (info->type_stack != NULL
	  && ! ieee_buffer_emptyp (&info->type_stack->type.strdef));

  /* If we were ignoring this struct definition because it was a
     duplicate definition, just through away whatever bytes we have
     accumulated.  Leave the type on the stack.  */
  if (info->type_stack->type.ignorep)
    return TRUE;

  /* If this is not a duplicate definition of this tag, then localp
     will be FALSE, and we can put it in the global type block.
     FIXME: We should avoid outputting duplicate definitions which are
     the same.  */
  if (! info->type_stack->type.localp)
    {
      /* Make sure we have started the global type block.  */
      if (ieee_buffer_emptyp (&info->global_types))
	{
	  if (! ieee_change_buffer (info, &info->global_types)
	      || ! ieee_write_byte (info, (int) ieee_bb_record_enum)
	      || ! ieee_write_byte (info, 2)
	      || ! ieee_write_number (info, 0)
	      || ! ieee_write_id (info, ""))
	    return FALSE;
	}
      pb = &info->global_types;
    }
  else
    {
      /* Make sure we have started the types block.  */
      if (ieee_buffer_emptyp (&info->types))
	{
	  if (! ieee_change_buffer (info, &info->types)
	      || ! ieee_write_byte (info, (int) ieee_bb_record_enum)
	      || ! ieee_write_byte (info, 1)
	      || ! ieee_write_number (info, 0)
	      || ! ieee_write_id (info, info->modname))
	    return FALSE;
	}
      pb = &info->types;
    }

  /* Append the struct definition to the types.  */
  if (! ieee_append_buffer (info, pb, &info->type_stack->type.strdef)
      || ! ieee_init_buffer (info, &info->type_stack->type.strdef))
    return FALSE;

  /* Leave the struct on the type stack.  */

  return TRUE;
}