#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_12__ {unsigned int (* dis_hash ) (char*,unsigned long) ;int /*<<< orphan*/  (* dis_hash_p ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  insn; struct TYPE_11__* next; } ;
typedef  TYPE_1__ CGEN_INSN_LIST ;
typedef  TYPE_2__* CGEN_CPU_DESC ;

/* Variables and functions */
 scalar_t__ CGEN_CPU_ENDIAN (TYPE_2__*) ; 
 scalar_t__ CGEN_ENDIAN_BIG ; 
 unsigned long CGEN_INSN_BASE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CGEN_INSN_MASK_BITSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_insn_to_hash_chain (TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__**,unsigned int) ; 
 int /*<<< orphan*/  bfd_put_bits (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 unsigned int stub2 (char*,unsigned long) ; 

__attribute__((used)) static CGEN_INSN_LIST *
hash_insn_list (CGEN_CPU_DESC cd,
		const CGEN_INSN_LIST *insns,
		CGEN_INSN_LIST **htable,
		CGEN_INSN_LIST *hentbuf)
{
  int big_p = CGEN_CPU_ENDIAN (cd) == CGEN_ENDIAN_BIG;
  const CGEN_INSN_LIST *ilist;

  for (ilist = insns; ilist != NULL; ilist = ilist->next, ++ hentbuf)
    {
      unsigned int hash;
      char buf[4];
      unsigned long value;

      if (! (* cd->dis_hash_p) (ilist->insn))
	continue;

      /* We don't know whether the target uses the buffer or the base insn
	 to hash on, so set both up.  */

      value = CGEN_INSN_BASE_VALUE (ilist->insn);
      bfd_put_bits((bfd_vma) value,
		   buf,
		   CGEN_INSN_MASK_BITSIZE (ilist->insn),
		   big_p);
      hash = (* cd->dis_hash) (buf, value);
      add_insn_to_hash_chain (hentbuf, ilist->insn, htable, hash);
    }

  return hentbuf;
}