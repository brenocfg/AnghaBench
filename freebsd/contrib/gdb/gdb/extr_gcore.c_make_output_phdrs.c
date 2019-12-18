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
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int PF_R ; 
 int PF_W ; 
 int PF_X ; 
 int PT_LOAD ; 
 int PT_NOTE ; 
 int SEC_CODE ; 
 int SEC_READONLY ; 
 int bfd_get_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_record_phdr (int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bfd_section_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
make_output_phdrs (bfd *obfd, asection *osec, void *ignored)
{
  int p_flags = 0;
  int p_type;

  /* FIXME: these constants may only be applicable for ELF.  */
  if (strncmp (bfd_section_name (obfd, osec), "load", 4) == 0)
    p_type = PT_LOAD;
  else
    p_type = PT_NOTE;

  p_flags |= PF_R;	/* Segment is readable.  */
  if (!(bfd_get_section_flags (obfd, osec) & SEC_READONLY))
    p_flags |= PF_W;	/* Segment is writable.  */
  if (bfd_get_section_flags (obfd, osec) & SEC_CODE)
    p_flags |= PF_X;	/* Segment is executable.  */

  bfd_record_phdr (obfd, p_type, 1, p_flags, 0, 0, 0, 0, 1, &osec);
}