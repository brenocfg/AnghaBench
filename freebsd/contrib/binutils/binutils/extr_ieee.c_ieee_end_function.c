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
struct ieee_handle {int block_depth; scalar_t__ fnargcount; int /*<<< orphan*/  fnargs; int /*<<< orphan*/  fntype; int /*<<< orphan*/ * fnname; int /*<<< orphan*/  types; int /*<<< orphan*/  modname; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ieee_append_buffer (struct ieee_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ieee_bb_record_enum ; 
 scalar_t__ ieee_buffer_emptyp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_change_buffer (struct ieee_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_init_buffer (struct ieee_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_write_byte (struct ieee_handle*,int) ; 
 int /*<<< orphan*/  ieee_write_id (struct ieee_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_write_number (struct ieee_handle*,scalar_t__) ; 

__attribute__((used)) static bfd_boolean
ieee_end_function (void *p)
{
  struct ieee_handle *info = (struct ieee_handle *) p;

  assert (info->block_depth == 1);

  --info->block_depth;

  /* Now we can finish up fntype, and add it to the typdef section.
     At this point, fntype is the 'x' type up to the argument count,
     and fnargs is the argument types.  We must add the argument
     count, and we must add the level.  FIXME: We don't record varargs
     functions correctly.  In fact, stabs debugging does not give us
     enough information to do so.  */
  if (! ieee_change_buffer (info, &info->fntype)
      || ! ieee_write_number (info, info->fnargcount)
      || ! ieee_change_buffer (info, &info->fnargs)
      || ! ieee_write_number (info, 0))
    return FALSE;

  /* Make sure the typdef block has been started.  */
  if (ieee_buffer_emptyp (&info->types))
    {
      if (! ieee_change_buffer (info, &info->types)
	  || ! ieee_write_byte (info, (int) ieee_bb_record_enum)
	  || ! ieee_write_byte (info, 1)
	  || ! ieee_write_number (info, 0)
	  || ! ieee_write_id (info, info->modname))
	return FALSE;
    }

  if (! ieee_append_buffer (info, &info->types, &info->fntype)
      || ! ieee_append_buffer (info, &info->types, &info->fnargs))
    return FALSE;

  info->fnname = NULL;
  if (! ieee_init_buffer (info, &info->fntype)
      || ! ieee_init_buffer (info, &info->fnargs))
    return FALSE;
  info->fnargcount = 0;

  return TRUE;
}