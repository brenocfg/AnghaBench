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

/* Variables and functions */
 scalar_t__ ASM_INTEL ; 
 scalar_t__ X86_FILE_START_FLTUSED ; 
 scalar_t__ X86_FILE_START_VERSION_DIRECTIVE ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  darwin_file_start () ; 
 int /*<<< orphan*/  default_file_start () ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ix86_asm_dialect ; 

__attribute__((used)) static void
x86_file_start (void)
{
  default_file_start ();
#if TARGET_MACHO
  darwin_file_start ();
#endif
  if (X86_FILE_START_VERSION_DIRECTIVE)
    fputs ("\t.version\t\"01.01\"\n", asm_out_file);
  if (X86_FILE_START_FLTUSED)
    fputs ("\t.global\t__fltused\n", asm_out_file);
  if (ix86_asm_dialect == ASM_INTEL)
    fputs ("\t.intel_syntax\n", asm_out_file);
}