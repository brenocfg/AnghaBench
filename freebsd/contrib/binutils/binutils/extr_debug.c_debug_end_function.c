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
struct debug_handle {TYPE_1__* current_block; int /*<<< orphan*/ * current_function; int /*<<< orphan*/ * current_unit; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {int /*<<< orphan*/  end; int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  debug_error (int /*<<< orphan*/ ) ; 

bfd_boolean
debug_end_function (void *handle, bfd_vma addr)
{
  struct debug_handle *info = (struct debug_handle *) handle;

  if (info->current_unit == NULL
      || info->current_block == NULL
      || info->current_function == NULL)
    {
      debug_error (_("debug_end_function: no current function"));
      return FALSE;
    }

  if (info->current_block->parent != NULL)
    {
      debug_error (_("debug_end_function: some blocks were not closed"));
      return FALSE;
    }

  info->current_block->end = addr;

  info->current_function = NULL;
  info->current_block = NULL;

  return TRUE;
}