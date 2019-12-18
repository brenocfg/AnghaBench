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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_3__ {int /*<<< orphan*/  (* internal_label ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ asm_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_OUTPUT_ADDR_VEC_ELT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASM_OUTPUT_ADDR_VEC_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASM_OUTPUT_ADDR_VEC_START (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASM_OUTPUT_CASE_LABEL (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CODE_LABEL_NUMBER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXT_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ targetm ; 

__attribute__((used)) static void 
sparc_output_addr_vec (rtx vec)
{
  rtx lab = XEXP (vec, 0), body = XEXP (vec, 1);
  int idx, vlen = XVECLEN (body, 0);

#ifdef ASM_OUTPUT_ADDR_VEC_START  
  ASM_OUTPUT_ADDR_VEC_START (asm_out_file);
#endif

#ifdef ASM_OUTPUT_CASE_LABEL
  ASM_OUTPUT_CASE_LABEL (asm_out_file, "L", CODE_LABEL_NUMBER (lab),
			 NEXT_INSN (lab));
#else
  (*targetm.asm_out.internal_label) (asm_out_file, "L", CODE_LABEL_NUMBER (lab));
#endif

  for (idx = 0; idx < vlen; idx++)
    {
      ASM_OUTPUT_ADDR_VEC_ELT
	(asm_out_file, CODE_LABEL_NUMBER (XEXP (XVECEXP (body, 0, idx), 0)));
    }
    
#ifdef ASM_OUTPUT_ADDR_VEC_END
  ASM_OUTPUT_ADDR_VEC_END (asm_out_file);
#endif
}