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
struct vbase {int /*<<< orphan*/  vbasetype; struct vbase* next; } ;
struct type {int dummy; } ;

/* Variables and functions */
 struct type* TYPE_PRIMARY_BASE (struct type*) ; 
 scalar_t__ TYPE_RUNTIME_PTR (struct type*) ; 
 struct vbase* current_vbase_list ; 
 scalar_t__ virtual_base_index (int /*<<< orphan*/ ,struct type*) ; 
 int /*<<< orphan*/  virtual_base_list_aux (struct type*) ; 
 int virtual_base_list_length (struct type*) ; 

int
virtual_base_list_length_skip_primaries (struct type *dclass)
{
  int i;
  struct vbase *tmp_vbase;
  struct type *primary;

  primary = TYPE_RUNTIME_PTR (dclass) ? TYPE_PRIMARY_BASE (dclass) : NULL;

  if (!primary)
    return virtual_base_list_length (dclass);

  current_vbase_list = NULL;
  virtual_base_list_aux (dclass);

  for (i = 0, tmp_vbase = current_vbase_list; tmp_vbase != NULL; tmp_vbase = tmp_vbase->next)
    {
      if (virtual_base_index (tmp_vbase->vbasetype, primary) >= 0)
	continue;
      i++;
    }
  return i;
}