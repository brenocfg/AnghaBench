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
typedef  int /*<<< orphan*/  symbolS ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SET_INTERWORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_SET_THUMB (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int SEC_CODE ; 
 char* S_GET_NAME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THUMB_SET_FUNC (int /*<<< orphan*/ *,int) ; 
 int bfd_get_section_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwarf2_emit_label (int /*<<< orphan*/ *) ; 
 scalar_t__ label_is_thumb_function_name ; 
 int /*<<< orphan*/ * last_label_seen ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/  support_interwork ; 
 int /*<<< orphan*/  thumb_mode ; 

void
arm_frob_label (symbolS * sym)
{
  last_label_seen = sym;

  ARM_SET_THUMB (sym, thumb_mode);

#if defined OBJ_COFF || defined OBJ_ELF
  ARM_SET_INTERWORK (sym, support_interwork);
#endif

  /* Note - do not allow local symbols (.Lxxx) to be labeled
     as Thumb functions.  This is because these labels, whilst
     they exist inside Thumb code, are not the entry points for
     possible ARM->Thumb calls.	 Also, these labels can be used
     as part of a computed goto or switch statement.  eg gcc
     can generate code that looks like this:

		ldr  r2, [pc, .Laaa]
		lsl  r3, r3, #2
		ldr  r2, [r3, r2]
		mov  pc, r2

       .Lbbb:  .word .Lxxx
       .Lccc:  .word .Lyyy
       ..etc...
       .Laaa:	.word Lbbb

     The first instruction loads the address of the jump table.
     The second instruction converts a table index into a byte offset.
     The third instruction gets the jump address out of the table.
     The fourth instruction performs the jump.

     If the address stored at .Laaa is that of a symbol which has the
     Thumb_Func bit set, then the linker will arrange for this address
     to have the bottom bit set, which in turn would mean that the
     address computation performed by the third instruction would end
     up with the bottom bit set.  Since the ARM is capable of unaligned
     word loads, the instruction would then load the incorrect address
     out of the jump table, and chaos would ensue.  */
  if (label_is_thumb_function_name
      && (S_GET_NAME (sym)[0] != '.' || S_GET_NAME (sym)[1] != 'L')
      && (bfd_get_section_flags (stdoutput, now_seg) & SEC_CODE) != 0)
    {
      /* When the address of a Thumb function is taken the bottom
	 bit of that address should be set.  This will allow
	 interworking between Arm and Thumb functions to work
	 correctly.  */

      THUMB_SET_FUNC (sym, 1);

      label_is_thumb_function_name = FALSE;
    }

  dwarf2_emit_label (sym);
}