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
struct constant_pool {int /*<<< orphan*/  pool_insn; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (scalar_t__) ; 
 int /*<<< orphan*/  INSN_ADDRESSES_NEW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_insn_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_last_insn () ; 

__attribute__((used)) static void
s390_end_pool (struct constant_pool *pool, rtx insn)
{
  rtx pool_size = GEN_INT (pool->size + 8 /* alignment slop */);

  if (!insn)
    insn = get_last_insn ();

  pool->pool_insn = emit_insn_after (gen_pool (pool_size), insn);
  INSN_ADDRESSES_NEW (pool->pool_insn, -1);
}