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
struct constant_pool {int /*<<< orphan*/  insns; struct constant_pool* next; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_UID (int /*<<< orphan*/ ) ; 
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct constant_pool *
s390_find_pool (struct constant_pool *pool_list, rtx insn)
{
  struct constant_pool *pool;

  for (pool = pool_list; pool; pool = pool->next)
    if (bitmap_bit_p (pool->insns, INSN_UID (insn)))
      break;

  return pool;
}