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
struct internal_filehdr {scalar_t__ f_opthdr; unsigned int f_nscns; } ;
struct internal_aouthdr {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_target ;
typedef  scalar_t__ bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 void* bfd_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ bfd_bread (void*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_coff_aoutsz (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_coff_bad_format_hook (int /*<<< orphan*/ *,struct internal_filehdr*) ; 
 scalar_t__ bfd_coff_filhsz (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_coff_swap_aouthdr_in (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  bfd_coff_swap_filehdr_in (int /*<<< orphan*/ *,void*,struct internal_filehdr*) ; 
 scalar_t__ bfd_error_system_call ; 
 int /*<<< orphan*/  bfd_error_wrong_format ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_release (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* coff_real_object_p (int /*<<< orphan*/ *,unsigned int,struct internal_filehdr*,struct internal_aouthdr*) ; 

const bfd_target *
coff_object_p (bfd *abfd)
{
  bfd_size_type filhsz;
  bfd_size_type aoutsz;
  unsigned int nscns;
  void * filehdr;
  struct internal_filehdr internal_f;
  struct internal_aouthdr internal_a;

  /* Figure out how much to read.  */
  filhsz = bfd_coff_filhsz (abfd);
  aoutsz = bfd_coff_aoutsz (abfd);

  filehdr = bfd_alloc (abfd, filhsz);
  if (filehdr == NULL)
    return NULL;
  if (bfd_bread (filehdr, filhsz, abfd) != filhsz)
    {
      if (bfd_get_error () != bfd_error_system_call)
	bfd_set_error (bfd_error_wrong_format);
      bfd_release (abfd, filehdr);
      return NULL;
    }
  bfd_coff_swap_filehdr_in (abfd, filehdr, &internal_f);
  bfd_release (abfd, filehdr);

  /* The XCOFF format has two sizes for the f_opthdr.  SMALL_AOUTSZ
     (less than aoutsz) used in object files and AOUTSZ (equal to
     aoutsz) in executables.  The bfd_coff_swap_aouthdr_in function
     expects this header to be aoutsz bytes in length, so we use that
     value in the call to bfd_alloc below.  But we must be careful to
     only read in f_opthdr bytes in the call to bfd_bread.  We should
     also attempt to catch corrupt or non-COFF binaries with a strange
     value for f_opthdr.  */
  if (! bfd_coff_bad_format_hook (abfd, &internal_f)
      || internal_f.f_opthdr > aoutsz)
    {
      bfd_set_error (bfd_error_wrong_format);
      return NULL;
    }
  nscns = internal_f.f_nscns;

  if (internal_f.f_opthdr)
    {
      void * opthdr;

      opthdr = bfd_alloc (abfd, aoutsz);
      if (opthdr == NULL)
	return NULL;
      if (bfd_bread (opthdr, (bfd_size_type) internal_f.f_opthdr, abfd)
	  != internal_f.f_opthdr)
	{
	  bfd_release (abfd, opthdr);
	  return NULL;
	}
      bfd_coff_swap_aouthdr_in (abfd, opthdr, (void *) &internal_a);
      bfd_release (abfd, opthdr);
    }

  return coff_real_object_p (abfd, nscns, &internal_f,
			     (internal_f.f_opthdr != 0
			      ? &internal_a
			      : (struct internal_aouthdr *) NULL));
}