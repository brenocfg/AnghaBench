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
struct ieee_buflist {int dummy; } ;
struct TYPE_2__ {unsigned int indx; struct ieee_buflist fndef; scalar_t__ localp; } ;
struct ieee_type_stack {struct ieee_type_stack* next; TYPE_1__ type; } ;
struct ieee_handle {char* modname; struct ieee_type_stack* type_stack; struct ieee_buflist global_types; struct ieee_buflist types; } ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 unsigned int FALSE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ieee_type_stack*) ; 
 int /*<<< orphan*/  ieee_append_buffer (struct ieee_handle*,struct ieee_buflist*,struct ieee_buflist*) ; 
 scalar_t__ ieee_bb_record_enum ; 
 scalar_t__ ieee_buffer_emptyp (struct ieee_buflist*) ; 
 int /*<<< orphan*/  ieee_change_buffer (struct ieee_handle*,struct ieee_buflist*) ; 
 int /*<<< orphan*/  ieee_write_byte (struct ieee_handle*,int) ; 
 int /*<<< orphan*/  ieee_write_id (struct ieee_handle*,char*) ; 
 int /*<<< orphan*/  ieee_write_number (struct ieee_handle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
ieee_pop_type_used (struct ieee_handle *info, bfd_boolean used)
{
  struct ieee_type_stack *ts;
  unsigned int ret;

  ts = info->type_stack;
  assert (ts != NULL);

  /* If this is a function type, and we need it, we need to append the
     actual definition to the typedef block now.  */
  if (used && ! ieee_buffer_emptyp (&ts->type.fndef))
    {
      struct ieee_buflist *buflist;

      if (ts->type.localp)
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
	  buflist = &info->types;
	}
      else
	{
	  /* Make sure we started the global type block.  */
	  if (ieee_buffer_emptyp (&info->global_types))
	    {
	      if (! ieee_change_buffer (info, &info->global_types)
		  || ! ieee_write_byte (info, (int) ieee_bb_record_enum)
		  || ! ieee_write_byte (info, 2)
		  || ! ieee_write_number (info, 0)
		  || ! ieee_write_id (info, ""))
		return FALSE;
	    }
	  buflist = &info->global_types;
	}

      if (! ieee_append_buffer (info, buflist, &ts->type.fndef))
	return FALSE;
    }

  ret = ts->type.indx;
  info->type_stack = ts->next;
  free (ts);
  return ret;
}