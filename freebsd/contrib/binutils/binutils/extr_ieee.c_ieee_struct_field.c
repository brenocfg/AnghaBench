#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ieee_handle {unsigned int name_indx; TYPE_5__* type_stack; } ;
typedef  enum debug_visibility { ____Placeholder_debug_visibility } debug_visibility ;
typedef  unsigned int bfd_vma ;
typedef  int bfd_boolean ;
struct TYPE_9__ {unsigned int size; int unsignedp; int referencep; int localp; char const* name; int /*<<< orphan*/  strdef; TYPE_3__* classdef; } ;
struct TYPE_10__ {TYPE_4__ type; TYPE_2__* next; } ;
struct TYPE_8__ {unsigned int indx; int pmisccount; int /*<<< orphan*/  refs; int /*<<< orphan*/  pmiscbuf; } ;
struct TYPE_6__ {scalar_t__ ignorep; int /*<<< orphan*/  strdef; } ;
struct TYPE_7__ {TYPE_1__ type; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ieee_atn_record_enum ; 
 int /*<<< orphan*/  ieee_buffer_emptyp (int /*<<< orphan*/ *) ; 
 scalar_t__ ieee_change_buffer (struct ieee_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_define_type (struct ieee_handle*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ ieee_nn_record ; 
 unsigned int ieee_pop_type (struct ieee_handle*) ; 
 int /*<<< orphan*/  ieee_pop_unused_type (struct ieee_handle*) ; 
 unsigned int ieee_vis_to_flags (int) ; 
 int /*<<< orphan*/  ieee_write_2bytes (struct ieee_handle*,int) ; 
 int /*<<< orphan*/  ieee_write_asn (struct ieee_handle*,unsigned int,int) ; 
 int /*<<< orphan*/  ieee_write_atn65 (struct ieee_handle*,unsigned int,char const*) ; 
 int /*<<< orphan*/  ieee_write_byte (struct ieee_handle*,int) ; 
 scalar_t__ ieee_write_id (struct ieee_handle*,char const*) ; 
 scalar_t__ ieee_write_number (struct ieee_handle*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
ieee_struct_field (void *p, const char *name, bfd_vma bitpos, bfd_vma bitsize,
		   enum debug_visibility visibility)
{
  struct ieee_handle *info = (struct ieee_handle *) p;
  unsigned int size;
  bfd_boolean unsignedp;
  bfd_boolean referencep;
  bfd_boolean localp;
  unsigned int indx;
  bfd_vma offset;

  assert (info->type_stack != NULL
	  && info->type_stack->next != NULL
	  && ! ieee_buffer_emptyp (&info->type_stack->next->type.strdef));

  /* If we are ignoring this struct definition, just pop and ignore
     the type.  */
  if (info->type_stack->next->type.ignorep)
    {
      ieee_pop_unused_type (info);
      return TRUE;
    }

  size = info->type_stack->type.size;
  unsignedp = info->type_stack->type.unsignedp;
  referencep = info->type_stack->type.referencep;
  localp = info->type_stack->type.localp;
  indx = ieee_pop_type (info);

  if (localp)
    info->type_stack->type.localp = TRUE;

  if (info->type_stack->type.classdef != NULL)
    {
      unsigned int flags;
      unsigned int nindx;

      /* This is a class.  We must add a description of this field to
         the class records we are building.  */

      flags = ieee_vis_to_flags (visibility);
      nindx = info->type_stack->type.classdef->indx;
      if (! ieee_change_buffer (info,
				&info->type_stack->type.classdef->pmiscbuf)
	  || ! ieee_write_asn (info, nindx, 'd')
	  || ! ieee_write_asn (info, nindx, flags)
	  || ! ieee_write_atn65 (info, nindx, name)
	  || ! ieee_write_atn65 (info, nindx, name))
	return FALSE;
      info->type_stack->type.classdef->pmisccount += 4;

      if (referencep)
	{
	  unsigned int nindx;

	  /* We need to output a record recording that this field is
             really of reference type.  We put this on the refs field
             of classdef, so that it can be appended to the C++
             records after the class is defined.  */

	  nindx = info->name_indx;
	  ++info->name_indx;

	  if (! ieee_change_buffer (info,
				    &info->type_stack->type.classdef->refs)
	      || ! ieee_write_byte (info, (int) ieee_nn_record)
	      || ! ieee_write_number (info, nindx)
	      || ! ieee_write_id (info, "")
	      || ! ieee_write_2bytes (info, (int) ieee_atn_record_enum)
	      || ! ieee_write_number (info, nindx)
	      || ! ieee_write_number (info, 0)
	      || ! ieee_write_number (info, 62)
	      || ! ieee_write_number (info, 80)
	      || ! ieee_write_number (info, 4)
	      || ! ieee_write_asn (info, nindx, 'R')
	      || ! ieee_write_asn (info, nindx, 3)
	      || ! ieee_write_atn65 (info, nindx, info->type_stack->type.name)
	      || ! ieee_write_atn65 (info, nindx, name))
	    return FALSE;
	}
    }

  /* If the bitsize doesn't match the expected size, we need to output
     a bitfield type.  */
  if (size == 0 || bitsize == 0 || bitsize == size * 8)
    offset = bitpos / 8;
  else
    {
      if (! ieee_define_type (info, 0, unsignedp,
			      info->type_stack->type.localp)
	  || ! ieee_write_number (info, 'g')
	  || ! ieee_write_number (info, unsignedp ? 0 : 1)
	  || ! ieee_write_number (info, bitsize)
	  || ! ieee_write_number (info, indx))
	return FALSE;
      indx = ieee_pop_type (info);
      offset = bitpos;
    }

  /* Switch to the struct we are building in order to output this
     field definition.  */
  return (ieee_change_buffer (info, &info->type_stack->type.strdef)
	  && ieee_write_id (info, name)
	  && ieee_write_number (info, indx)
	  && ieee_write_number (info, offset));
}