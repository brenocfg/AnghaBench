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
struct symbol {int dummy; } ;
struct TYPE_2__ {int (* read_needs_frame ) (struct symbol*) ;} ;

/* Variables and functions */
#define  LOC_ARG 149 
#define  LOC_BASEREG 148 
#define  LOC_BASEREG_ARG 147 
#define  LOC_BLOCK 146 
#define  LOC_COMPUTED 145 
#define  LOC_COMPUTED_ARG 144 
#define  LOC_CONST 143 
#define  LOC_CONST_BYTES 142 
#define  LOC_HP_THREAD_LOCAL_STATIC 141 
#define  LOC_INDIRECT 140 
#define  LOC_LABEL 139 
#define  LOC_LOCAL 138 
#define  LOC_LOCAL_ARG 137 
#define  LOC_OPTIMIZED_OUT 136 
#define  LOC_REF_ARG 135 
#define  LOC_REGISTER 134 
#define  LOC_REGPARM 133 
#define  LOC_REGPARM_ADDR 132 
#define  LOC_STATIC 131 
#define  LOC_TYPEDEF 130 
#define  LOC_UNDEF 129 
#define  LOC_UNRESOLVED 128 
 int SYMBOL_CLASS (struct symbol*) ; 
 TYPE_1__* SYMBOL_OPS (struct symbol*) ; 
 int stub1 (struct symbol*) ; 

int
symbol_read_needs_frame (struct symbol *sym)
{
  switch (SYMBOL_CLASS (sym))
    {
      /* All cases listed explicitly so that gcc -Wall will detect it if
         we failed to consider one.  */
    case LOC_COMPUTED:
    case LOC_COMPUTED_ARG:
      /* FIXME: cagney/2004-01-26: It should be possible to
	 unconditionally call the SYMBOL_OPS method when available.
	 Unfortunately DWARF 2 stores the frame-base (instead of the
	 function) location in a function's symbol.  Oops!  For the
	 moment enable this when/where applicable.  */
      return SYMBOL_OPS (sym)->read_needs_frame (sym);

    case LOC_REGISTER:
    case LOC_ARG:
    case LOC_REF_ARG:
    case LOC_REGPARM:
    case LOC_REGPARM_ADDR:
    case LOC_LOCAL:
    case LOC_LOCAL_ARG:
    case LOC_BASEREG:
    case LOC_BASEREG_ARG:
    case LOC_HP_THREAD_LOCAL_STATIC:
      return 1;

    case LOC_UNDEF:
    case LOC_CONST:
    case LOC_STATIC:
    case LOC_INDIRECT:
    case LOC_TYPEDEF:

    case LOC_LABEL:
      /* Getting the address of a label can be done independently of the block,
         even if some *uses* of that address wouldn't work so well without
         the right frame.  */

    case LOC_BLOCK:
    case LOC_CONST_BYTES:
    case LOC_UNRESOLVED:
    case LOC_OPTIMIZED_OUT:
      return 0;
    }
  return 1;
}