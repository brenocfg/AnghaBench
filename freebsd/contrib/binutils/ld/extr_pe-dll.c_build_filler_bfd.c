#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * the_bfd; } ;
typedef  TYPE_1__ lang_input_statement_type ;

/* Variables and functions */
 int SEC_ALLOC ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_KEEP ; 
 int SEC_LOAD ; 
 int /*<<< orphan*/ * bfd_create (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_arch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_mach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_make_section_old_way (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bfd_set_arch_mach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bfd_set_section_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * edata_s ; 
 int /*<<< orphan*/  edata_sz ; 
 int /*<<< orphan*/  einfo (char*) ; 
 int /*<<< orphan*/ * filler_bfd ; 
 TYPE_1__* lang_add_input_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lang_input_file_is_fake_enum ; 
 int /*<<< orphan*/  ldlang_add_file (TYPE_1__*) ; 
 int /*<<< orphan*/  output_bfd ; 
 int /*<<< orphan*/ * reloc_s ; 

__attribute__((used)) static void
build_filler_bfd (int include_edata)
{
  lang_input_statement_type *filler_file;
  filler_file = lang_add_input_file ("dll stuff",
				     lang_input_file_is_fake_enum,
				     NULL);
  filler_file->the_bfd = filler_bfd = bfd_create ("dll stuff", output_bfd);
  if (filler_bfd == NULL
      || !bfd_set_arch_mach (filler_bfd,
			     bfd_get_arch (output_bfd),
			     bfd_get_mach (output_bfd)))
    {
      einfo ("%X%P: can not create BFD: %E\n");
      return;
    }

  if (include_edata)
    {
      edata_s = bfd_make_section_old_way (filler_bfd, ".edata");
      if (edata_s == NULL
	  || !bfd_set_section_flags (filler_bfd, edata_s,
				     (SEC_HAS_CONTENTS
				      | SEC_ALLOC
				      | SEC_LOAD
				      | SEC_KEEP
				      | SEC_IN_MEMORY)))
	{
	  einfo ("%X%P: can not create .edata section: %E\n");
	  return;
	}
      bfd_set_section_size (filler_bfd, edata_s, edata_sz);
    }

  reloc_s = bfd_make_section_old_way (filler_bfd, ".reloc");
  if (reloc_s == NULL
      || !bfd_set_section_flags (filler_bfd, reloc_s,
				 (SEC_HAS_CONTENTS
				  | SEC_ALLOC
				  | SEC_LOAD
				  | SEC_KEEP
				  | SEC_IN_MEMORY)))
    {
      einfo ("%X%P: can not create .reloc section: %E\n");
      return;
    }

  bfd_set_section_size (filler_bfd, reloc_s, 0);

  ldlang_add_file (filler_file);
}