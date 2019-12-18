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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ BB_END (scalar_t__) ; 
 scalar_t__ BLOCK_FOR_INSN (scalar_t__) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  delete_insn_chain (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  purge_dead_edges (scalar_t__) ; 

void
delete_insn_chain_and_edges (rtx first, rtx last)
{
  bool purge = false;

  if (INSN_P (last)
      && BLOCK_FOR_INSN (last)
      && BB_END (BLOCK_FOR_INSN (last)) == last)
    purge = true;
  delete_insn_chain (first, last);
  if (purge)
    purge_dead_edges (BLOCK_FOR_INSN (last));
}