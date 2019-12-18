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
struct tree_opt_pass {int static_pass_number; struct tree_opt_pass* next; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct tree_opt_pass*,struct tree_opt_pass*,int) ; 
 struct tree_opt_pass* xmalloc (int) ; 

__attribute__((used)) static struct tree_opt_pass **
next_pass_1 (struct tree_opt_pass **list, struct tree_opt_pass *pass)
{
  /* A nonzero static_pass_number indicates that the
     pass is already in the list.  */
  if (pass->static_pass_number)
    {
      struct tree_opt_pass *new;

      new = xmalloc (sizeof (*new));
      memcpy (new, pass, sizeof (*new));

      /* Indicate to register_dump_files that this pass has duplicates,
         and so it should rename the dump file.  The first instance will
         be -1, and be number of duplicates = -static_pass_number - 1.
         Subsequent instances will be > 0 and just the duplicate number.  */
      if (pass->name)
        {
          pass->static_pass_number -= 1;
          new->static_pass_number = -pass->static_pass_number;
	}
      
      *list = new;
    }
  else
    {
      pass->static_pass_number = -1;
      *list = pass;
    }  
  
  return &(*list)->next;
          
}