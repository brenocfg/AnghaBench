#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data; TYPE_1__* procs; } ;
struct TYPE_3__ {int (* prompt_proc_p ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__* current_interpreter ; 
 int stub1 (int /*<<< orphan*/ ) ; 

int
current_interp_display_prompt_p (void)
{
  if (current_interpreter == NULL
      || current_interpreter->procs->prompt_proc_p == NULL)
    return 0;
  else
    return current_interpreter->procs->prompt_proc_p (current_interpreter->
						      data);
}