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
struct dwarf2_line_info {unsigned int filenum; unsigned int line; } ;
typedef  int /*<<< orphan*/  addressT ;

/* Variables and functions */
 scalar_t__ DEBUG_DWARF2 ; 
 scalar_t__ debug_type ; 
 int /*<<< orphan*/  dwarf2_gen_line_info_1 (int /*<<< orphan*/ *,struct dwarf2_line_info*) ; 
 int /*<<< orphan*/  frag_now ; 
 int /*<<< orphan*/  now_seg ; 
 int /*<<< orphan*/ * symbol_temp_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dwarf2_gen_line_info (addressT ofs, struct dwarf2_line_info *loc)
{
  static unsigned int line = -1;
  static unsigned int filenum = -1;

  symbolS *sym;

  /* Early out for as-yet incomplete location information.  */
  if (loc->filenum == 0 || loc->line == 0)
    return;

  /* Don't emit sequences of line symbols for the same line when the
     symbols apply to assembler code.  It is necessary to emit
     duplicate line symbols when a compiler asks for them, because GDB
     uses them to determine the end of the prologue.  */
  if (debug_type == DEBUG_DWARF2
      && line == loc->line && filenum == loc->filenum)
    return;

  line = loc->line;
  filenum = loc->filenum;

  sym = symbol_temp_new (now_seg, ofs, frag_now);
  dwarf2_gen_line_info_1 (sym, loc);
}