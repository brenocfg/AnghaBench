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
struct debug_lineno {scalar_t__ file; unsigned long* linenos; struct debug_lineno* next; void** addrs; } ;
struct debug_handle {scalar_t__ current_file; struct debug_lineno* current_lineno; TYPE_1__* current_unit; } ;
typedef  void* bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_2__ {struct debug_lineno* linenos; } ;

/* Variables and functions */
 unsigned int DEBUG_LINENO_COUNT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  debug_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_lineno*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

bfd_boolean
debug_record_line (void *handle, unsigned long lineno, bfd_vma addr)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_lineno *l;
  unsigned int i;

  if (info->current_unit == NULL)
    {
      debug_error (_("debug_record_line: no current unit"));
      return FALSE;
    }

  l = info->current_lineno;
  if (l != NULL && l->file == info->current_file)
    {
      for (i = 0; i < DEBUG_LINENO_COUNT; i++)
	{
	  if (l->linenos[i] == (unsigned long) -1)
	    {
	      l->linenos[i] = lineno;
	      l->addrs[i] = addr;
	      return TRUE;
	    }
	}
    }

  /* If we get here, then either 1) there is no current_lineno
     structure, which means this is the first line number in this
     compilation unit, 2) the current_lineno structure is for a
     different file, or 3) the current_lineno structure is full.
     Regardless, we want to allocate a new debug_lineno structure, put
     it in the right place, and make it the new current_lineno
     structure.  */

  l = (struct debug_lineno *) xmalloc (sizeof *l);
  memset (l, 0, sizeof *l);

  l->file = info->current_file;
  l->linenos[0] = lineno;
  l->addrs[0] = addr;
  for (i = 1; i < DEBUG_LINENO_COUNT; i++)
    l->linenos[i] = (unsigned long) -1;

  if (info->current_lineno != NULL)
    info->current_lineno->next = l;
  else
    info->current_unit->linenos = l;

  info->current_lineno = l;

  return TRUE;
}