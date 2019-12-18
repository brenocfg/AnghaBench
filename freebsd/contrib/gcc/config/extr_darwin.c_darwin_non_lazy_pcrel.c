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
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_OUTPUT_LABELREF (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ SYMBOL_REF ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 char* machopic_indirection_name (int /*<<< orphan*/ ,int) ; 

void
darwin_non_lazy_pcrel (FILE *file, rtx addr)
{
  const char *nlp_name;

  gcc_assert (GET_CODE (addr) == SYMBOL_REF);

  nlp_name = machopic_indirection_name (addr, /*stub_p=*/false);
  fputs ("\t.long\t", file);
  ASM_OUTPUT_LABELREF (file, nlp_name);
  fputs ("-.", file);
}