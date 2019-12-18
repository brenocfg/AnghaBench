#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_21__ {TYPE_1__* xvec; } ;
typedef  TYPE_2__ bfd ;
struct TYPE_20__ {scalar_t__ flavour; } ;

/* Variables and functions */
 int APCS_26_FLAG (TYPE_2__*) ; 
 int APCS_FLOAT_FLAG (TYPE_2__*) ; 
 scalar_t__ APCS_SET (TYPE_2__*) ; 
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ INTERWORK_FLAG (TYPE_2__*) ; 
 scalar_t__ INTERWORK_SET (TYPE_2__*) ; 
 int PIC_FLAG (TYPE_2__*) ; 
 int /*<<< orphan*/  SET_APCS_FLAGS (TYPE_2__*,int) ; 
 int /*<<< orphan*/  SET_INTERWORK_FLAG (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (char const*,TYPE_2__*,TYPE_2__*,...) ; 
 int /*<<< orphan*/  bfd_arm_merge_machines (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 int /*<<< orphan*/  bfd_get_arch (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_get_mach (TYPE_2__*) ; 
 int /*<<< orphan*/  bfd_set_arch_mach (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_target_coff_flavour ; 

__attribute__((used)) static bfd_boolean
coff_arm_merge_private_bfd_data (bfd * ibfd, bfd * obfd)
{
  BFD_ASSERT (ibfd != NULL && obfd != NULL);

  if (ibfd == obfd)
    return TRUE;

  /* If the two formats are different we cannot merge anything.
     This is not an error, since it is permissable to change the
     input and output formats.  */
  if (   ibfd->xvec->flavour != bfd_target_coff_flavour
      || obfd->xvec->flavour != bfd_target_coff_flavour)
    return TRUE;

  /* Determine what should happen if the input ARM architecture
     does not match the output ARM architecture.  */
  if (! bfd_arm_merge_machines (ibfd, obfd))
    return FALSE;

  /* Verify that the APCS is the same for the two BFDs.  */
  if (APCS_SET (ibfd))
    {
      if (APCS_SET (obfd))
	{
	  /* If the src and dest have different APCS flag bits set, fail.  */
	  if (APCS_26_FLAG (obfd) != APCS_26_FLAG (ibfd))
	    {
	      _bfd_error_handler
		/* xgettext: c-format */
		(_("ERROR: %B is compiled for APCS-%d, whereas %B is compiled for APCS-%d"),
		 ibfd, obfd,
		 APCS_26_FLAG (ibfd) ? 26 : 32,
		 APCS_26_FLAG (obfd) ? 26 : 32
		 );

	      bfd_set_error (bfd_error_wrong_format);
	      return FALSE;
	    }

	  if (APCS_FLOAT_FLAG (obfd) != APCS_FLOAT_FLAG (ibfd))
	    {
	      const char *msg;

	      if (APCS_FLOAT_FLAG (ibfd))
		/* xgettext: c-format */
		msg = _("ERROR: %B passes floats in float registers, whereas %B passes them in integer registers");
	      else
		/* xgettext: c-format */
		msg = _("ERROR: %B passes floats in integer registers, whereas %B passes them in float registers");

	      _bfd_error_handler (msg, ibfd, obfd);

	      bfd_set_error (bfd_error_wrong_format);
	      return FALSE;
	    }

	  if (PIC_FLAG (obfd) != PIC_FLAG (ibfd))
	    {
	      const char * msg;

	      if (PIC_FLAG (ibfd))
		/* xgettext: c-format */
		msg = _("ERROR: %B is compiled as position independent code, whereas target %B is absolute position");
	      else
		/* xgettext: c-format */
		msg = _("ERROR: %B is compiled as absolute position code, whereas target %B is position independent");
	      _bfd_error_handler (msg, ibfd, obfd);

	      bfd_set_error (bfd_error_wrong_format);
	      return FALSE;
	    }
	}
      else
	{
	  SET_APCS_FLAGS (obfd, APCS_26_FLAG (ibfd) | APCS_FLOAT_FLAG (ibfd) | PIC_FLAG (ibfd));

	  /* Set up the arch and fields as well as these are probably wrong.  */
	  bfd_set_arch_mach (obfd, bfd_get_arch (ibfd), bfd_get_mach (ibfd));
	}
    }

  /* Check the interworking support.  */
  if (INTERWORK_SET (ibfd))
    {
      if (INTERWORK_SET (obfd))
	{
	  /* If the src and dest differ in their interworking issue a warning.  */
	  if (INTERWORK_FLAG (obfd) != INTERWORK_FLAG (ibfd))
	    {
	      const char * msg;

	      if (INTERWORK_FLAG (ibfd))
		/* xgettext: c-format */
		msg = _("Warning: %B supports interworking, whereas %B does not");
	      else
		/* xgettext: c-format */
		msg = _("Warning: %B does not support interworking, whereas %B does");

	      _bfd_error_handler (msg, ibfd, obfd);
	    }
	}
      else
	{
	  SET_INTERWORK_FLAG (obfd, INTERWORK_FLAG (ibfd));
	}
    }

  return TRUE;
}