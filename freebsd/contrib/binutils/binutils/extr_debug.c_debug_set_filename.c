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
struct debug_unit {char const* filename; struct debug_unit* next; struct debug_unit* files; } ;
struct debug_handle {int /*<<< orphan*/ * current_lineno; int /*<<< orphan*/ * current_block; int /*<<< orphan*/ * current_function; struct debug_unit* current_unit; struct debug_unit* units; struct debug_unit* current_file; } ;
struct debug_file {char const* filename; struct debug_file* next; struct debug_file* files; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct debug_unit*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xmalloc (int) ; 

bfd_boolean
debug_set_filename (void *handle, const char *name)
{
  struct debug_handle *info = (struct debug_handle *) handle;
  struct debug_file *nfile;
  struct debug_unit *nunit;

  if (name == NULL)
    name = "";

  nfile = (struct debug_file *) xmalloc (sizeof *nfile);
  memset (nfile, 0, sizeof *nfile);

  nfile->filename = name;

  nunit = (struct debug_unit *) xmalloc (sizeof *nunit);
  memset (nunit, 0, sizeof *nunit);

  nunit->files = nfile;
  info->current_file = nfile;

  if (info->current_unit != NULL)
    info->current_unit->next = nunit;
  else
    {
      assert (info->units == NULL);
      info->units = nunit;
    }

  info->current_unit = nunit;

  info->current_function = NULL;
  info->current_block = NULL;
  info->current_lineno = NULL;

  return TRUE;
}