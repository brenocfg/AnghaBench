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
struct constant_pool {scalar_t__ size; int /*<<< orphan*/  insns; void* pool_insn; void* first_insn; int /*<<< orphan*/  label; int /*<<< orphan*/ * execute; int /*<<< orphan*/ ** constants; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int NR_C_MODES ; 
 void* NULL_RTX ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static struct constant_pool *
s390_alloc_pool (void)
{
  struct constant_pool *pool;
  int i;

  pool = (struct constant_pool *) xmalloc (sizeof *pool);
  pool->next = NULL;
  for (i = 0; i < NR_C_MODES; i++)
    pool->constants[i] = NULL;

  pool->execute = NULL;
  pool->label = gen_label_rtx ();
  pool->first_insn = NULL_RTX;
  pool->pool_insn = NULL_RTX;
  pool->insns = BITMAP_ALLOC (NULL);
  pool->size = 0;

  return pool;
}