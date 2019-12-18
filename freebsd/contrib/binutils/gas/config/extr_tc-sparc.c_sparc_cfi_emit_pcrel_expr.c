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
typedef  int /*<<< orphan*/  expressionS ;

/* Variables and functions */
 int /*<<< orphan*/  emit_expr (int /*<<< orphan*/ *,unsigned int) ; 
 char* sparc_cons_special_reloc ; 
 int sparc_no_align_cons ; 

void
sparc_cfi_emit_pcrel_expr (expressionS *exp, unsigned int nbytes)
{
  sparc_cons_special_reloc = "disp";
  sparc_no_align_cons = 1;
  emit_expr (exp, nbytes);
  sparc_no_align_cons = 0;
  sparc_cons_special_reloc = NULL;
}