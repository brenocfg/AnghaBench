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
#define  DEBUG_DWARF 133 
#define  DEBUG_DWARF2 132 
#define  DEBUG_ECOFF 131 
#define  DEBUG_NONE 130 
#define  DEBUG_STABS 129 
#define  DEBUG_UNSPECIFIED 128 
 int debug_type ; 
 int /*<<< orphan*/  ecoff_generate_asm_lineno () ; 
 int /*<<< orphan*/  stabs_generate_asm_lineno () ; 

void
generate_lineno_debug (void)
{
  switch (debug_type)
    {
    case DEBUG_UNSPECIFIED:
    case DEBUG_NONE:
    case DEBUG_DWARF:
      break;
    case DEBUG_STABS:
      stabs_generate_asm_lineno ();
      break;
    case DEBUG_ECOFF:
      ecoff_generate_asm_lineno ();
      break;
    case DEBUG_DWARF2:
      /* ??? We could here indicate to dwarf2dbg.c that something
	 has changed.  However, since there is additional backend
	 support that is required (calling dwarf2_emit_insn), we
	 let dwarf2dbg.c call as_where on its own.  */
      break;
    }
}