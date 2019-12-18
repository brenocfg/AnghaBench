#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_9__ {int flags; TYPE_2__* section; } ;
typedef  TYPE_3__ asymbol ;
typedef  int /*<<< orphan*/  asection ;
typedef  int /*<<< orphan*/  arelent ;
struct TYPE_8__ {TYPE_1__* output_section; } ;
struct TYPE_7__ {int /*<<< orphan*/ * owner; } ;

/* Variables and functions */
 int BSF_LOCAL ; 
 int BSF_SECTION_SYM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ _ (char*) ; 
 scalar_t__ bfd_reloc_ok ; 
 scalar_t__ bfd_reloc_outofrange ; 
 scalar_t__ gprel32_with_gp (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,scalar_t__) ; 
 scalar_t__ score_elf_final_gp (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,char**,scalar_t__*) ; 

__attribute__((used)) static bfd_reloc_status_type
score_elf_gprel32_reloc (bfd *abfd, arelent *reloc_entry, asymbol *symbol,
			void *data, asection *input_section, bfd *output_bfd,
			char **error_message)
{
  bfd_boolean relocatable;
  bfd_reloc_status_type ret;
  bfd_vma gp;

  /* R_SCORE_GPREL32 relocations are defined for local symbols only.  */
  if (output_bfd != NULL
      && (symbol->flags & BSF_SECTION_SYM) == 0
      && (symbol->flags & BSF_LOCAL) != 0)
    {
      *error_message = (char *)
	_("32bits gp relative relocation occurs for an external symbol");
      return bfd_reloc_outofrange;
    }

  if (output_bfd != NULL)
    relocatable = TRUE;
  else
    {
      relocatable = FALSE;
      output_bfd = symbol->section->output_section->owner;
    }

  ret = score_elf_final_gp (output_bfd, symbol, relocatable, error_message, &gp);
  if (ret != bfd_reloc_ok)
    return ret;

  gp = 0;   /* FIXME.  */
  return gprel32_with_gp (abfd, symbol, reloc_entry, input_section,
			  relocatable, data, gp);
}