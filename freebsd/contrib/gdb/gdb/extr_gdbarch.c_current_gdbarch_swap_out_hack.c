#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gdbarch_swap {TYPE_1__* source; int /*<<< orphan*/  swap; struct gdbarch_swap* next; } ;
struct gdbarch {struct gdbarch_swap* swap; } ;
struct TYPE_2__ {int /*<<< orphan*/  sizeof_data; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 struct gdbarch* current_gdbarch ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct gdbarch *
current_gdbarch_swap_out_hack (void)
{
  struct gdbarch *old_gdbarch = current_gdbarch;
  struct gdbarch_swap *curr;

  gdb_assert (old_gdbarch != NULL);
  for (curr = old_gdbarch->swap;
       curr != NULL;
       curr = curr->next)
    {
      memcpy (curr->swap, curr->source->data, curr->source->sizeof_data);
      memset (curr->source->data, 0, curr->source->sizeof_data);
    }
  current_gdbarch = NULL;
  return old_gdbarch;
}