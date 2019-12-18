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
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int APCS_26_FLAG (int /*<<< orphan*/ *) ; 
 int APCS_FLOAT_FLAG (int /*<<< orphan*/ *) ; 
 scalar_t__ APCS_SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int F_APCS26 ; 
 int F_APCS_26 ; 
 int F_APCS_FLOAT ; 
 int F_INTERWORK ; 
 int F_PIC ; 
 int INTERWORK_FLAG (int /*<<< orphan*/ *) ; 
 scalar_t__ INTERWORK_SET (int /*<<< orphan*/ *) ; 
 int PIC_FLAG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_APCS_FLAGS (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SET_INTERWORK_FLAG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
_bfd_coff_arm_set_private_flags (bfd * abfd, flagword flags)
{
  flagword flag;

  BFD_ASSERT (abfd != NULL);

  flag = (flags & F_APCS26) ? F_APCS_26 : 0;

  /* Make sure that the APCS field has not been initialised to the opposite
     value.  */
  if (APCS_SET (abfd)
      && (   (APCS_26_FLAG    (abfd) != flag)
	  || (APCS_FLOAT_FLAG (abfd) != (flags & F_APCS_FLOAT))
	  || (PIC_FLAG        (abfd) != (flags & F_PIC))
	  ))
    return FALSE;

  flag |= (flags & (F_APCS_FLOAT | F_PIC));

  SET_APCS_FLAGS (abfd, flag);

  flag = (flags & F_INTERWORK);

  /* If the BFD has already had its interworking flag set, but it
     is different from the value that we have been asked to set,
     then assume that that merged code will not support interworking
     and set the flag accordingly.  */
  if (INTERWORK_SET (abfd) && (INTERWORK_FLAG (abfd) != flag))
    {
      if (flag)
	/* xgettext: c-format */
	_bfd_error_handler (_("Warning: Not setting interworking flag of %B since it has already been specified as non-interworking"),
			    abfd);
      else
	/* xgettext: c-format */
	_bfd_error_handler (_("Warning: Clearing the interworking flag of %B due to outside request"),
			    abfd);
      flag = 0;
    }

  SET_INTERWORK_FLAG (abfd, flag);

  return TRUE;
}