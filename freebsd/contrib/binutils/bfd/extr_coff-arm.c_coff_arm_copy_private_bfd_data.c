#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_14__ {scalar_t__ xvec; } ;
typedef  TYPE_1__ bfd ;

/* Variables and functions */
 int APCS_26_FLAG (TYPE_1__*) ; 
 int APCS_FLOAT_FLAG (TYPE_1__*) ; 
 scalar_t__ APCS_SET (TYPE_1__*) ; 
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INTERWORK_FLAG (TYPE_1__*) ; 
 scalar_t__ INTERWORK_SET (TYPE_1__*) ; 
 int PIC_FLAG (TYPE_1__*) ; 
 int /*<<< orphan*/  SET_APCS_FLAGS (TYPE_1__*,int) ; 
 int /*<<< orphan*/  SET_INTERWORK_FLAG (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_error_handler (char*,TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static bfd_boolean
coff_arm_copy_private_bfd_data (bfd * src, bfd * dest)
{
  BFD_ASSERT (src != NULL && dest != NULL);

  if (src == dest)
    return TRUE;

  /* If the destination is not in the same format as the source, do not do
     the copy.  */
  if (src->xvec != dest->xvec)
    return TRUE;

  /* Copy the flags field.  */
  if (APCS_SET (src))
    {
      if (APCS_SET (dest))
	{
	  /* If the src and dest have different APCS flag bits set, fail.  */
	  if (APCS_26_FLAG (dest) != APCS_26_FLAG (src))
	    return FALSE;

	  if (APCS_FLOAT_FLAG (dest) != APCS_FLOAT_FLAG (src))
	    return FALSE;

	  if (PIC_FLAG (dest) != PIC_FLAG (src))
	    return FALSE;
	}
      else
	SET_APCS_FLAGS (dest, APCS_26_FLAG (src) | APCS_FLOAT_FLAG (src)
			| PIC_FLAG (src));
    }

  if (INTERWORK_SET (src))
    {
      if (INTERWORK_SET (dest))
	{
	  /* If the src and dest have different interworking flags then turn
	     off the interworking bit.  */
	  if (INTERWORK_FLAG (dest) != INTERWORK_FLAG (src))
	    {
	      if (INTERWORK_FLAG (dest))
		{
		  /* xgettext:c-format */
		  _bfd_error_handler (("\
Warning: Clearing the interworking flag of %B because non-interworking code in %B has been linked with it"),
				      dest, src);
		}

	      SET_INTERWORK_FLAG (dest, 0);
	    }
	}
      else
	{
	  SET_INTERWORK_FLAG (dest, INTERWORK_FLAG (src));
	}
    }

  return TRUE;
}