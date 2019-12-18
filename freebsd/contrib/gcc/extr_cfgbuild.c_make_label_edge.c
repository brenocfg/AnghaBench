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
typedef  int /*<<< orphan*/  sbitmap ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FOR_INSN (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cached_make_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
make_label_edge (sbitmap edge_cache, basic_block src, rtx label, int flags)
{
  gcc_assert (LABEL_P (label));

  /* If the label was never emitted, this insn is junk, but avoid a
     crash trying to refer to BLOCK_FOR_INSN (label).  This can happen
     as a result of a syntax error and a diagnostic has already been
     printed.  */

  if (INSN_UID (label) == 0)
    return;

  cached_make_edge (edge_cache, src, BLOCK_FOR_INSN (label), flags);
}