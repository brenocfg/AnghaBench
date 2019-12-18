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
 scalar_t__ delete_insn (scalar_t__) ; 
 int /*<<< orphan*/  purge_dead_edges (scalar_t__) ; 

rtx
delete_insn_and_edges (rtx insn)
{
  rtx x;
  bool purge = false;

  if (INSN_P (insn)
      && BLOCK_FOR_INSN (insn)
      && BB_END (BLOCK_FOR_INSN (insn)) == insn)
    purge = true;
  x = delete_insn (insn);
  if (purge)
    purge_dead_edges (BLOCK_FOR_INSN (insn));
  return x;
}