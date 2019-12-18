#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int (* asm_hash ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* asm_hash_p ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  insn; struct TYPE_8__* next; } ;
typedef  TYPE_1__ CGEN_INSN_LIST ;
typedef  TYPE_2__* CGEN_CPU_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  CGEN_INSN_MNEMONIC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 unsigned int stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CGEN_INSN_LIST *
hash_insn_list (CGEN_CPU_DESC cd,
		const CGEN_INSN_LIST *insns,
		CGEN_INSN_LIST **htable,
		CGEN_INSN_LIST *hentbuf)
{
  const CGEN_INSN_LIST *ilist;

  for (ilist = insns; ilist != NULL; ilist = ilist->next, ++ hentbuf)
    {
      unsigned int hash;

      if (! (* cd->asm_hash_p) (ilist->insn))
	continue;
      hash = (* cd->asm_hash) (CGEN_INSN_MNEMONIC (ilist->insn));
      hentbuf->next = htable[hash];
      hentbuf->insn = ilist->insn;
      htable[hash] = hentbuf;
    }

  return hentbuf;
}