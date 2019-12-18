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
struct ui_out {int dummy; } ;
struct interp {struct ui_out* interpreter_out; } ;
struct TYPE_2__ {struct ui_out* interpreter_out; } ;

/* Variables and functions */
 TYPE_1__* current_interpreter ; 

struct ui_out *
interp_ui_out (struct interp *interp)
{
  if (interp != NULL)
    return interp->interpreter_out;

  return current_interpreter->interpreter_out;
}