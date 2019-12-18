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
struct target_ops {int dummy; } ;
struct load_module_desc {int dummy; } ;
struct so_list {int loaded; int /*<<< orphan*/  name; int /*<<< orphan*/  pa64_solib_desc_addr; struct load_module_desc pa64_solib_desc; struct so_list* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  objfile_obstack; } ;
typedef  int LONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int auto_solib_limit ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  obsavestring (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa64_solib_add_solib_objfile (struct so_list*,char*,int,int) ; 
 int /*<<< orphan*/  pa64_solib_load_symbols (struct so_list*,char*,int,int /*<<< orphan*/ ,struct target_ops*) ; 
 int pa64_solib_sizeof_symbol_table (char*) ; 
 int pa64_solib_total_st_size ; 
 struct so_list* so_list_head ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 TYPE_1__* symfile_objfile ; 
 scalar_t__ target_read_memory (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
add_to_solist (int from_tty, char *dll_path, int readsyms,
	       struct load_module_desc *load_module_desc_p,
	       CORE_ADDR load_module_desc_addr, struct target_ops *target)
{
  struct so_list *new_so, *so_list_tail;
  int pa64_solib_st_size_threshhold_exceeded;
  LONGEST st_size;

  if (symfile_objfile == NULL)
    return;

  so_list_tail = so_list_head;
  /* Find the end of the list of shared objects.  */
  while (so_list_tail && so_list_tail->next)
    {
      if (strcmp (so_list_tail->name, dll_path) == 0)
	return;
      so_list_tail = so_list_tail->next;
    }

  if (so_list_tail && strcmp (so_list_tail->name, dll_path) == 0)
    return;

  /* Add the shared library to the so_list_head list */
  new_so = (struct so_list *) xmalloc (sizeof (struct so_list));
  memset ((char *)new_so, 0, sizeof (struct so_list));
  if (so_list_head == NULL)
    {
      so_list_head = new_so;
      so_list_tail = new_so;
    }
  else
    {
      so_list_tail->next = new_so;
      so_list_tail = new_so;
    }

  /* Initialize the new_so */
  if (load_module_desc_p)
    {
      new_so->pa64_solib_desc = *load_module_desc_p;
    }
  else
    {
      if (target_read_memory (load_module_desc_addr, 
			      (char*) &new_so->pa64_solib_desc,
			      sizeof(struct load_module_desc))
	  != 0)
      {
	error ("Error while reading in dynamic library %s", dll_path);
      }
    }
  
  new_so->pa64_solib_desc_addr = load_module_desc_addr;
  new_so->loaded = 1;
  new_so->name = obsavestring (dll_path, strlen(dll_path),
			       &symfile_objfile->objfile_obstack);

  /* If we are not going to load the library, tell the user if we
     haven't already and return.  */

  st_size = pa64_solib_sizeof_symbol_table (dll_path);
  pa64_solib_st_size_threshhold_exceeded =
       !from_tty 
    && readsyms
    && (  (st_size + pa64_solib_total_st_size) 
	> (auto_solib_limit * (LONGEST) (1024 * 1024)));
  if (pa64_solib_st_size_threshhold_exceeded)
    {
      pa64_solib_add_solib_objfile (new_so, dll_path, from_tty, 1);
      return;
    } 

  /* Now read in debug info. */
  pa64_solib_total_st_size += st_size;

  /* This fills in new_so->objfile, among others. */
  pa64_solib_load_symbols (new_so, 
			   dll_path,
			   from_tty, 
			   0,
			   target);
  return;
}