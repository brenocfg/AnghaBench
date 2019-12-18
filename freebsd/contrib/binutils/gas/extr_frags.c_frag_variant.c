#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
typedef  int /*<<< orphan*/  relax_substateT ;
typedef  int /*<<< orphan*/  relax_stateT ;
typedef  int /*<<< orphan*/  offsetT ;
struct TYPE_5__ {scalar_t__ opinfo; scalar_t__ opindex; scalar_t__ insn; } ;
struct TYPE_7__ {int fr_var; char* fr_opcode; int /*<<< orphan*/  fr_line; int /*<<< orphan*/  fr_file; TYPE_1__ fr_cgen; int /*<<< orphan*/  fr_offset; int /*<<< orphan*/ * fr_symbol; int /*<<< orphan*/  fr_subtype; int /*<<< orphan*/  fr_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  frch_obstack; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC_FRAG_INIT (TYPE_3__*) ; 
 int /*<<< orphan*/  as_where (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frag_new (int) ; 
 TYPE_3__* frag_now ; 
 TYPE_2__* frchain_now ; 
 char* obstack_next_free (int /*<<< orphan*/ *) ; 

char *
frag_variant (relax_stateT type, int max_chars, int var,
	      relax_substateT subtype, symbolS *symbol, offsetT offset,
	      char *opcode)
{
  register char *retval;

  retval = obstack_next_free (&frchain_now->frch_obstack);
  frag_now->fr_var = var;
  frag_now->fr_type = type;
  frag_now->fr_subtype = subtype;
  frag_now->fr_symbol = symbol;
  frag_now->fr_offset = offset;
  frag_now->fr_opcode = opcode;
#ifdef USING_CGEN
  frag_now->fr_cgen.insn = 0;
  frag_now->fr_cgen.opindex = 0;
  frag_now->fr_cgen.opinfo = 0;
#endif
#ifdef TC_FRAG_INIT
  TC_FRAG_INIT (frag_now);
#endif
  as_where (&frag_now->fr_file, &frag_now->fr_line);
  frag_new (max_chars);
  return (retval);
}