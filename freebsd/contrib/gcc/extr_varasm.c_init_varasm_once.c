#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* init_sections ) () ;} ;
struct TYPE_4__ {TYPE_1__ asm_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_SECTION_ASM_OP ; 
 int /*<<< orphan*/  CTORS_SECTION_ASM_OP ; 
 int /*<<< orphan*/  DATA_SECTION_ASM_OP ; 
 int /*<<< orphan*/  DTORS_SECTION_ASM_OP ; 
 int /*<<< orphan*/  READONLY_DATA_SECTION_ASM_OP ; 
 int /*<<< orphan*/  SBSS_SECTION_ASM_OP ; 
 int /*<<< orphan*/  SDATA_SECTION_ASM_OP ; 
 int SECTION_BSS ; 
 int SECTION_CODE ; 
 int SECTION_COMMON ; 
 int SECTION_WRITE ; 
 int /*<<< orphan*/  TEXT_SECTION_ASM_OP ; 
 void* bss_noswitch_section ; 
 void* bss_section ; 
 void* comm_section ; 
 int /*<<< orphan*/  const_alias_set ; 
 int /*<<< orphan*/  const_desc_eq ; 
 int /*<<< orphan*/  const_desc_hash ; 
 void* const_desc_htab ; 
 int /*<<< orphan*/  create_constant_pool () ; 
 void* ctors_section ; 
 void* data_section ; 
 void* dtors_section ; 
 int /*<<< orphan*/  emit_bss ; 
 int /*<<< orphan*/  emit_common ; 
 int /*<<< orphan*/  emit_local ; 
 int /*<<< orphan*/  emit_tls_common ; 
 void* get_noswitch_section (int,int /*<<< orphan*/ ) ; 
 void* get_unnamed_section (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htab_create_ggc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* lcomm_section ; 
 int /*<<< orphan*/  new_alias_set () ; 
 int /*<<< orphan*/  object_block_entry_eq ; 
 int /*<<< orphan*/  object_block_entry_hash ; 
 void* object_block_htab ; 
 int /*<<< orphan*/  output_section_asm_op ; 
 int /*<<< orphan*/ * readonly_data_section ; 
 void* sbss_section ; 
 void* sdata_section ; 
 int /*<<< orphan*/  section_entry_eq ; 
 int /*<<< orphan*/  section_entry_hash ; 
 void* section_htab ; 
 int /*<<< orphan*/  shared_constant_pool ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_2__ targetm ; 
 int /*<<< orphan*/ * text_section ; 
 void* tls_comm_section ; 

void
init_varasm_once (void)
{
  section_htab = htab_create_ggc (31, section_entry_hash,
				  section_entry_eq, NULL);
  object_block_htab = htab_create_ggc (31, object_block_entry_hash,
				       object_block_entry_eq, NULL);
  const_desc_htab = htab_create_ggc (1009, const_desc_hash,
				     const_desc_eq, NULL);

  const_alias_set = new_alias_set ();
  shared_constant_pool = create_constant_pool ();

#ifdef TEXT_SECTION_ASM_OP
  text_section = get_unnamed_section (SECTION_CODE, output_section_asm_op,
				      TEXT_SECTION_ASM_OP);
#endif

#ifdef DATA_SECTION_ASM_OP
  data_section = get_unnamed_section (SECTION_WRITE, output_section_asm_op,
				      DATA_SECTION_ASM_OP);
#endif

#ifdef SDATA_SECTION_ASM_OP
  sdata_section = get_unnamed_section (SECTION_WRITE, output_section_asm_op,
				       SDATA_SECTION_ASM_OP);
#endif

#ifdef READONLY_DATA_SECTION_ASM_OP
  readonly_data_section = get_unnamed_section (0, output_section_asm_op,
					       READONLY_DATA_SECTION_ASM_OP);
#endif

#ifdef CTORS_SECTION_ASM_OP
  ctors_section = get_unnamed_section (0, output_section_asm_op,
				       CTORS_SECTION_ASM_OP);
#endif

#ifdef DTORS_SECTION_ASM_OP
  dtors_section = get_unnamed_section (0, output_section_asm_op,
				       DTORS_SECTION_ASM_OP);
#endif

#ifdef BSS_SECTION_ASM_OP
  bss_section = get_unnamed_section (SECTION_WRITE | SECTION_BSS,
				     output_section_asm_op,
				     BSS_SECTION_ASM_OP);
#endif

#ifdef SBSS_SECTION_ASM_OP
  sbss_section = get_unnamed_section (SECTION_WRITE | SECTION_BSS,
				      output_section_asm_op,
				      SBSS_SECTION_ASM_OP);
#endif

  tls_comm_section = get_noswitch_section (SECTION_WRITE | SECTION_BSS
					   | SECTION_COMMON, emit_tls_common);
  lcomm_section = get_noswitch_section (SECTION_WRITE | SECTION_BSS
					| SECTION_COMMON, emit_local);
  comm_section = get_noswitch_section (SECTION_WRITE | SECTION_BSS
				       | SECTION_COMMON, emit_common);

#if defined ASM_OUTPUT_ALIGNED_BSS || defined ASM_OUTPUT_BSS
  bss_noswitch_section = get_noswitch_section (SECTION_WRITE | SECTION_BSS,
					       emit_bss);
#endif

  targetm.asm_out.init_sections ();

  if (readonly_data_section == NULL)
    readonly_data_section = text_section;
}