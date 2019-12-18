#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_14__ {int /*<<< orphan*/ * sym; } ;
typedef  TYPE_1__ segment_info_type ;
typedef  TYPE_2__* segT ;
struct TYPE_17__ {int /*<<< orphan*/  flags; } ;
struct TYPE_16__ {int /*<<< orphan*/  name; } ;
struct TYPE_15__ {TYPE_4__* symbol; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_SECTION_SYM ; 
 int /*<<< orphan*/  EMIT_SECTION_SYMBOLS ; 
 int /*<<< orphan*/  S_CLEAR_EXTERNAL (int /*<<< orphan*/ *) ; 
 TYPE_2__* S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_SET_SEGMENT (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ obj_sec_sym_ok_for_reloc (TYPE_2__*) ; 
 TYPE_1__* seg_info (TYPE_2__*) ; 
 int /*<<< orphan*/ * symbol_create (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_find (int /*<<< orphan*/ ) ; 
 TYPE_6__* symbol_get_bfdsym (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_new (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol_set_bfdsym (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  symbol_set_frag (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ symbol_table_frozen ; 
 TYPE_2__* undefined_section ; 
 int /*<<< orphan*/  zero_address_frag ; 

symbolS *
section_symbol (segT sec)
{
  segment_info_type *seginfo = seg_info (sec);
  symbolS *s;

  if (seginfo == 0)
    abort ();
  if (seginfo->sym)
    return seginfo->sym;

#ifndef EMIT_SECTION_SYMBOLS
#define EMIT_SECTION_SYMBOLS 1
#endif

  if (! EMIT_SECTION_SYMBOLS || symbol_table_frozen)
    {
      /* Here we know it won't be going into the symbol table.  */
      s = symbol_create (sec->symbol->name, sec, 0, &zero_address_frag);
    }
  else
    {
      segT seg;
      s = symbol_find (sec->symbol->name);
      /* We have to make sure it is the right symbol when we
	 have multiple sections with the same section name.  */
      if (s == NULL
	  || ((seg = S_GET_SEGMENT (s)) != sec
	      && seg != undefined_section))
	s = symbol_new (sec->symbol->name, sec, 0, &zero_address_frag);
      else if (seg == undefined_section)
	{
	  S_SET_SEGMENT (s, sec);
	  symbol_set_frag (s, &zero_address_frag);
	}
    }

  S_CLEAR_EXTERNAL (s);

  /* Use the BFD section symbol, if possible.  */
  if (obj_sec_sym_ok_for_reloc (sec))
    symbol_set_bfdsym (s, sec->symbol);
  else
    symbol_get_bfdsym (s)->flags |= BSF_SECTION_SYM;

  seginfo->sym = s;
  return s;
}