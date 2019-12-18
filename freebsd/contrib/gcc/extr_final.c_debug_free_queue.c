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

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * symbol_queue ; 
 scalar_t__ symbol_queue_size ; 

void
debug_free_queue (void)
{
  if (symbol_queue)
    {
      free (symbol_queue);
      symbol_queue = NULL;
      symbol_queue_size = 0;
    }
}