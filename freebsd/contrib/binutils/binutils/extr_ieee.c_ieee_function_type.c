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
struct ieee_modified_type {scalar_t__ function; } ;
struct ieee_handle {TYPE_2__* type_stack; } ;
struct ieee_buflist {int dummy; } ;
typedef  unsigned int bfd_vma ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_3__ {scalar_t__ indx; struct ieee_buflist fndef; scalar_t__ localp; } ;
struct TYPE_4__ {TYPE_1__ type; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ builtin_void ; 
 int /*<<< orphan*/  free (unsigned int*) ; 
 int /*<<< orphan*/  ieee_define_named_type (struct ieee_handle*,char const*,unsigned int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct ieee_buflist*) ; 
 struct ieee_modified_type* ieee_get_modified_info (void*,unsigned int) ; 
 int /*<<< orphan*/  ieee_init_buffer (struct ieee_handle*,struct ieee_buflist*) ; 
 unsigned int ieee_pop_type (struct ieee_handle*) ; 
 scalar_t__ ieee_push_type (struct ieee_handle*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ieee_write_number (struct ieee_handle*,unsigned int) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static bfd_boolean
ieee_function_type (void *p, int argcount, bfd_boolean varargs)
{
  struct ieee_handle *info = (struct ieee_handle *) p;
  bfd_boolean localp;
  unsigned int *args = NULL;
  int i;
  unsigned int retindx;
  struct ieee_buflist fndef;
  struct ieee_modified_type *m;

  localp = FALSE;

  if (argcount > 0)
    {
      args = (unsigned int *) xmalloc (argcount * sizeof *args);
      for (i = argcount - 1; i >= 0; i--)
	{
	  if (info->type_stack->type.localp)
	    localp = TRUE;
	  args[i] = ieee_pop_type (info);
	}
    }
  else if (argcount < 0)
    varargs = FALSE;

  if (info->type_stack->type.localp)
    localp = TRUE;
  retindx = ieee_pop_type (info);

  m = NULL;
  if (argcount < 0 && ! localp)
    {
      m = ieee_get_modified_info (p, retindx);
      if (m == NULL)
	return FALSE;

      if (m->function > 0)
	return ieee_push_type (info, m->function, 0, TRUE, FALSE);
    }

  /* An attribute of 0x41 means that the frame and push mask are
     unknown.  */
  if (! ieee_init_buffer (info, &fndef)
      || ! ieee_define_named_type (info, (const char *) NULL,
				   (unsigned int) -1, 0, TRUE, localp,
				   &fndef)
      || ! ieee_write_number (info, 'x')
      || ! ieee_write_number (info, 0x41)
      || ! ieee_write_number (info, 0)
      || ! ieee_write_number (info, 0)
      || ! ieee_write_number (info, retindx)
      || ! ieee_write_number (info, (bfd_vma) argcount + (varargs ? 1 : 0)))
    return FALSE;
  if (argcount > 0)
    {
      for (i = 0; i < argcount; i++)
	if (! ieee_write_number (info, args[i]))
	  return FALSE;
      free (args);
    }
  if (varargs)
    {
      /* A varargs function is represented by writing out the last
         argument as type void *, although this makes little sense.  */
      if (! ieee_write_number (info, (bfd_vma) builtin_void + 32))
	return FALSE;
    }

  if (! ieee_write_number (info, 0))
    return FALSE;

  /* We wrote the information into fndef, in case we don't need it.
     It will be appended to info->types by ieee_pop_type.  */
  info->type_stack->type.fndef = fndef;

  if (m != NULL)
    m->function = info->type_stack->type.indx;

  return TRUE;
}