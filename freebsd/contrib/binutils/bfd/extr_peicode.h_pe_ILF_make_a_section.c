#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct coff_section_tdata {int dummy; } ;
struct TYPE_15__ {scalar_t__ data; scalar_t__ sym_index; int /*<<< orphan*/  abfd; TYPE_1__* bim; int /*<<< orphan*/  sec_index; } ;
typedef  TYPE_2__ pe_ILF_vars ;
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd_size_type ;
typedef  TYPE_3__* asection_ptr ;
struct TYPE_17__ {scalar_t__ i; } ;
struct TYPE_16__ {scalar_t__ contents; struct coff_section_tdata* used_by_bfd; scalar_t__ target_index; } ;
struct TYPE_14__ {scalar_t__ buffer; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  BSF_LOCAL ; 
 int SEC_ALLOC ; 
 int SEC_HAS_CONTENTS ; 
 int SEC_IN_MEMORY ; 
 int SEC_KEEP ; 
 int SEC_LOAD ; 
 TYPE_3__* bfd_make_section_old_way (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  bfd_set_section_alignment (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  bfd_set_section_flags (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  bfd_set_section_size (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* coff_section_data (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  pe_ILF_make_a_symbol (TYPE_2__*,char*,char const*,TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static asection_ptr
pe_ILF_make_a_section (pe_ILF_vars * vars,
		       const char *  name,
		       unsigned int  size,
		       flagword      extra_flags)
{
  asection_ptr sec;
  flagword     flags;

  sec = bfd_make_section_old_way (vars->abfd, name);
  if (sec == NULL)
    return NULL;

  flags = SEC_HAS_CONTENTS | SEC_ALLOC | SEC_LOAD | SEC_KEEP | SEC_IN_MEMORY;

  bfd_set_section_flags (vars->abfd, sec, flags | extra_flags);

  (void) bfd_set_section_alignment (vars->abfd, sec, 2);

  /* Check that we will not run out of space.  */
  BFD_ASSERT (vars->data + size < vars->bim->buffer + vars->bim->size);

  /* Set the section size and contents.  The actual
     contents are filled in by our parent.  */
  bfd_set_section_size (vars->abfd, sec, (bfd_size_type) size);
  sec->contents = vars->data;
  sec->target_index = vars->sec_index ++;

  /* Advance data pointer in the vars structure.  */
  vars->data += size;

  /* Skip the padding byte if it was not needed.
     The logic here is that if the string length is odd,
     then the entire string length, including the null byte,
     is even and so the extra, padding byte, is not needed.  */
  if (size & 1)
    vars->data --;

  /* Create a coff_section_tdata structure for our use.  */
  sec->used_by_bfd = (struct coff_section_tdata *) vars->data;
  vars->data += sizeof (struct coff_section_tdata);

  BFD_ASSERT (vars->data <= vars->bim->buffer + vars->bim->size);

  /* Create a symbol to refer to this section.  */
  pe_ILF_make_a_symbol (vars, "", name, sec, BSF_LOCAL);

  /* Cache the index to the symbol in the coff_section_data structure.  */
  coff_section_data (vars->abfd, sec)->i = vars->sym_index - 1;

  return sec;
}