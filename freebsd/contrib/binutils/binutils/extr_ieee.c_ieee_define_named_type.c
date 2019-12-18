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
struct ieee_buflist {int dummy; } ;
struct ieee_handle {unsigned int type_indx; unsigned int name_indx; char const* modname; struct ieee_buflist global_types; struct ieee_buflist types; } ;
typedef  int bfd_boolean ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ ieee_bb_record_enum ; 
 int /*<<< orphan*/  ieee_buffer_emptyp (struct ieee_buflist*) ; 
 int /*<<< orphan*/  ieee_change_buffer (struct ieee_handle*,struct ieee_buflist*) ; 
 scalar_t__ ieee_nn_record ; 
 int /*<<< orphan*/  ieee_push_type (struct ieee_handle*,unsigned int,unsigned int,int,int) ; 
 scalar_t__ ieee_ty_record_enum ; 
 scalar_t__ ieee_write_byte (struct ieee_handle*,int) ; 
 scalar_t__ ieee_write_id (struct ieee_handle*,char const*) ; 
 scalar_t__ ieee_write_number (struct ieee_handle*,unsigned int) ; 

__attribute__((used)) static bfd_boolean
ieee_define_named_type (struct ieee_handle *info, const char *name,
			unsigned int indx, unsigned int size,
			bfd_boolean unsignedp, bfd_boolean localp,
			struct ieee_buflist *buflist)
{
  unsigned int type_indx;
  unsigned int name_indx;

  if (indx != (unsigned int) -1)
    type_indx = indx;
  else
    {
      type_indx = info->type_indx;
      ++info->type_indx;
    }

  name_indx = info->name_indx;
  ++info->name_indx;

  if (name == NULL)
    name = "";

  /* If we were given a buffer, use it; otherwise, use either the
     local or the global type information, and make sure that the type
     block is started.  */
  if (buflist != NULL)
    {
      if (! ieee_change_buffer (info, buflist))
	return FALSE;
    }
  else if (localp)
    {
      if (! ieee_buffer_emptyp (&info->types))
	{
	  if (! ieee_change_buffer (info, &info->types))
	    return FALSE;
	}
      else
	{
	  if (! ieee_change_buffer (info, &info->types)
	      || ! ieee_write_byte (info, (int) ieee_bb_record_enum)
	      || ! ieee_write_byte (info, 1)
	      || ! ieee_write_number (info, 0)
	      || ! ieee_write_id (info, info->modname))
	    return FALSE;
	}
    }
  else
    {
      if (! ieee_buffer_emptyp (&info->global_types))
	{
	  if (! ieee_change_buffer (info, &info->global_types))
	    return FALSE;
	}
      else
	{
	  if (! ieee_change_buffer (info, &info->global_types)
	      || ! ieee_write_byte (info, (int) ieee_bb_record_enum)
	      || ! ieee_write_byte (info, 2)
	      || ! ieee_write_number (info, 0)
	      || ! ieee_write_id (info, ""))
	    return FALSE;
	}
    }

  /* Push the new type on the type stack, write out an NN record, and
     write out the start of a TY record.  The caller will then finish
     the TY record.  */
  if (! ieee_push_type (info, type_indx, size, unsignedp, localp))
    return FALSE;

  return (ieee_write_byte (info, (int) ieee_nn_record)
	  && ieee_write_number (info, name_indx)
	  && ieee_write_id (info, name)
	  && ieee_write_byte (info, (int) ieee_ty_record_enum)
	  && ieee_write_number (info, type_indx)
	  && ieee_write_byte (info, 0xce)
	  && ieee_write_number (info, name_indx));
}