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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/ * symbol_queue ; 
 int symbol_queue_index ; 
 int symbol_queue_size ; 
 int /*<<< orphan*/ * xrealloc (int /*<<< orphan*/ *,int) ; 

void
debug_queue_symbol (tree decl)
{
  if (symbol_queue_index >= symbol_queue_size)
    {
      symbol_queue_size += 10;
      symbol_queue = xrealloc (symbol_queue,
			       symbol_queue_size * sizeof (tree));
    }

  symbol_queue[symbol_queue_index++] = decl;
}