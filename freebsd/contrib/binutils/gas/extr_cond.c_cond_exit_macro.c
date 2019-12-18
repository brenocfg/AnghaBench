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
struct conditional_frame {int macro_nest; struct conditional_frame* previous_cframe; } ;

/* Variables and functions */
 int /*<<< orphan*/  cond_obstack ; 
 struct conditional_frame* current_cframe ; 
 int /*<<< orphan*/  obstack_free (int /*<<< orphan*/ *,struct conditional_frame*) ; 

void
cond_exit_macro (int nest)
{
  while (current_cframe != NULL && current_cframe->macro_nest >= nest)
    {
      struct conditional_frame *hold;

      hold = current_cframe;
      current_cframe = current_cframe->previous_cframe;
      obstack_free (&cond_obstack, hold);
    }
}