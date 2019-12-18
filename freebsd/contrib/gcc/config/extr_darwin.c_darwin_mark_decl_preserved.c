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
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 

void
darwin_mark_decl_preserved (const char *name)
{
  fprintf (asm_out_file, ".no_dead_strip ");
  assemble_name (asm_out_file, name);
  fputc ('\n', asm_out_file);
}