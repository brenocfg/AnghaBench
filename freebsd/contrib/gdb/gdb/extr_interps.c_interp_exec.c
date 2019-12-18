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
struct interp {int /*<<< orphan*/  data; TYPE_1__* procs; } ;
struct TYPE_2__ {int (* exec_proc ) (int /*<<< orphan*/ ,char const*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,char const*) ; 

int
interp_exec (struct interp *interp, const char *command_str)
{
  if (interp->procs->exec_proc != NULL)
    {
      return interp->procs->exec_proc (interp->data, command_str);
    }
  return 0;
}