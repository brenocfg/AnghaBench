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
struct TYPE_2__ {void* within; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_DEBUG ; 
 int /*<<< orphan*/  PPC_BIG_ENDIAN ; 
 int /*<<< orphan*/  bfd_set_private_flags (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  coff_section_from_bfd_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msolaris ; 
 int ppc_cie_data_alignment ; 
 int /*<<< orphan*/  ppc_coff_debug_section ; 
 int /*<<< orphan*/  ppc_current_section ; 
 void* ppc_data_csects ; 
 scalar_t__ ppc_flags ; 
 scalar_t__ ppc_obj64 ; 
 scalar_t__ ppc_previous_section ; 
 int /*<<< orphan*/  ppc_set_cpu () ; 
 int /*<<< orphan*/  ppc_setup_opcodes () ; 
 void* ppc_text_csects ; 
 int set_target_endian ; 
 int /*<<< orphan*/  stdoutput ; 
 TYPE_1__* symbol_get_tc (void*) ; 
 void* symbol_make (char*) ; 
 int /*<<< orphan*/  target_big_endian ; 
 int /*<<< orphan*/  text_section ; 

void
md_begin (void)
{
  ppc_set_cpu ();

  ppc_cie_data_alignment = ppc_obj64 ? -8 : -4;

#ifdef OBJ_ELF
  /* Set the ELF flags if desired.  */
  if (ppc_flags && !msolaris)
    bfd_set_private_flags (stdoutput, ppc_flags);
#endif

  ppc_setup_opcodes ();

  /* Tell the main code what the endianness is if it is not overridden
     by the user.  */
  if (!set_target_endian)
    {
      set_target_endian = 1;
      target_big_endian = PPC_BIG_ENDIAN;
    }

#ifdef OBJ_XCOFF
  ppc_coff_debug_section = coff_section_from_bfd_index (stdoutput, N_DEBUG);

  /* Create dummy symbols to serve as initial csects.  This forces the
     text csects to precede the data csects.  These symbols will not
     be output.  */
  ppc_text_csects = symbol_make ("dummy\001");
  symbol_get_tc (ppc_text_csects)->within = ppc_text_csects;
  ppc_data_csects = symbol_make ("dummy\001");
  symbol_get_tc (ppc_data_csects)->within = ppc_data_csects;
#endif

#ifdef TE_PE

  ppc_current_section = text_section;
  ppc_previous_section = 0;

#endif
}