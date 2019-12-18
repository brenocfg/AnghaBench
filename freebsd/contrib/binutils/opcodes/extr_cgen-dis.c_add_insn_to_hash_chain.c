#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/  const* insn; } ;
typedef  TYPE_1__ CGEN_INSN_LIST ;
typedef  int /*<<< orphan*/  CGEN_INSN ;

/* Variables and functions */
 int count_decodable_bits (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
add_insn_to_hash_chain (CGEN_INSN_LIST *hentbuf,
			const CGEN_INSN *insn,
			CGEN_INSN_LIST **htable,
			unsigned int hash)
{
  CGEN_INSN_LIST *current_buf;
  CGEN_INSN_LIST *previous_buf;
  int insn_decodable_bits;

  /* Add insns sorted by the number of decodable bits, in decreasing order.
     This ensures that any insn which is a special case of another will be
     checked first.  */
  insn_decodable_bits = count_decodable_bits (insn);
  previous_buf = NULL;
  for (current_buf = htable[hash]; current_buf != NULL;
       current_buf = current_buf->next)
    {
      int current_decodable_bits = count_decodable_bits (current_buf->insn);
      if (insn_decodable_bits >= current_decodable_bits)
	break;
      previous_buf = current_buf;
    }

  /* Now insert the new insn.  */
  hentbuf->insn = insn;
  hentbuf->next = current_buf;
  if (previous_buf == NULL)
    htable[hash] = hentbuf;
  else
    previous_buf->next = hentbuf;
}