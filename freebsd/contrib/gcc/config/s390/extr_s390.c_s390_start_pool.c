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
struct constant_pool {struct constant_pool* next; int /*<<< orphan*/  first_insn; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 struct constant_pool* s390_alloc_pool () ; 

__attribute__((used)) static struct constant_pool *
s390_start_pool (struct constant_pool **pool_list, rtx insn)
{
  struct constant_pool *pool, **prev;

  pool = s390_alloc_pool ();
  pool->first_insn = insn;

  for (prev = pool_list; *prev; prev = &(*prev)->next)
    ;
  *prev = pool;

  return pool;
}