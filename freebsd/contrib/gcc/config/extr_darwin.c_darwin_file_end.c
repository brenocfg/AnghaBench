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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_OUTPUT_ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  asm_out_file ; 
 size_t constructor_section ; 
 int /*<<< orphan*/ * darwin_sections ; 
 size_t destructor_section ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  machopic_finish (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  switch_to_section (int /*<<< orphan*/ ) ; 

void
darwin_file_end (void)
{
  machopic_finish (asm_out_file);
  if (strcmp (lang_hooks.name, "GNU C++") == 0)
    {
      switch_to_section (darwin_sections[constructor_section]);
      switch_to_section (darwin_sections[destructor_section]);
      ASM_OUTPUT_ALIGN (asm_out_file, 1);
    }
  fprintf (asm_out_file, "\t.subsections_via_symbols\n");
}