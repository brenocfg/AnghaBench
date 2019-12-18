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
struct function_range {char const* name; struct function_range* next; scalar_t__ seen_line; void* highpc; void* lowpc; } ;
struct dwarf2_cu {struct function_range* last_fn; struct function_range* first_fn; } ;
typedef  void* CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf2_tmp_obstack ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
add_to_cu_func_list (const char *name, CORE_ADDR lowpc, CORE_ADDR highpc,
		     struct dwarf2_cu *cu)
{
  struct function_range *thisfn;

  thisfn = (struct function_range *)
    obstack_alloc (&dwarf2_tmp_obstack, sizeof (struct function_range));
  thisfn->name = name;
  thisfn->lowpc = lowpc;
  thisfn->highpc = highpc;
  thisfn->seen_line = 0;
  thisfn->next = NULL;

  if (cu->last_fn == NULL)
      cu->first_fn = thisfn;
  else
      cu->last_fn->next = thisfn;

  cu->last_fn = thisfn;
}