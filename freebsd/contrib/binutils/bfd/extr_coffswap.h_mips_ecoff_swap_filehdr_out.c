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
struct internal_filehdr {int /*<<< orphan*/  f_target_id; int /*<<< orphan*/  f_flags; int /*<<< orphan*/  f_opthdr; int /*<<< orphan*/  f_nsyms; int /*<<< orphan*/  f_symptr; int /*<<< orphan*/  f_timdat; int /*<<< orphan*/  f_nscns; int /*<<< orphan*/  f_magic; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  f_target_id; int /*<<< orphan*/  f_flags; int /*<<< orphan*/  f_opthdr; int /*<<< orphan*/  f_nsyms; int /*<<< orphan*/  f_symptr; int /*<<< orphan*/  f_timdat; int /*<<< orphan*/  f_nscns; int /*<<< orphan*/  f_magic; } ;
typedef  TYPE_1__ FILHDR ;

/* Variables and functions */
 int /*<<< orphan*/  COFF_ADJUST_FILEHDR_OUT_POST (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  COFF_ADJUST_FILEHDR_OUT_PRE (int /*<<< orphan*/ *,void*,void*) ; 
 int /*<<< orphan*/  H_PUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_FILEHDR_SYMPTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int bfd_coff_filhsz (int /*<<< orphan*/ *) ; 

__attribute__((used)) static  unsigned int
coff_swap_filehdr_out (bfd *abfd, void * in, void * out)
{
  struct internal_filehdr *filehdr_in = (struct internal_filehdr *) in;
  FILHDR *filehdr_out = (FILHDR *) out;

#ifdef COFF_ADJUST_FILEHDR_OUT_PRE
  COFF_ADJUST_FILEHDR_OUT_PRE (abfd, in, out);
#endif
  H_PUT_16 (abfd, filehdr_in->f_magic, filehdr_out->f_magic);
  H_PUT_16 (abfd, filehdr_in->f_nscns, filehdr_out->f_nscns);
  H_PUT_32 (abfd, filehdr_in->f_timdat, filehdr_out->f_timdat);
  PUT_FILEHDR_SYMPTR (abfd, filehdr_in->f_symptr, filehdr_out->f_symptr);
  H_PUT_32 (abfd, filehdr_in->f_nsyms, filehdr_out->f_nsyms);
  H_PUT_16 (abfd, filehdr_in->f_opthdr, filehdr_out->f_opthdr);
  H_PUT_16 (abfd, filehdr_in->f_flags, filehdr_out->f_flags);
#ifdef TIC80_TARGET_ID
  H_PUT_16 (abfd, filehdr_in->f_target_id, filehdr_out->f_target_id);
#endif

#ifdef COFF_ADJUST_FILEHDR_OUT_POST
  COFF_ADJUST_FILEHDR_OUT_POST (abfd, in, out);
#endif
  return bfd_coff_filhsz (abfd);
}