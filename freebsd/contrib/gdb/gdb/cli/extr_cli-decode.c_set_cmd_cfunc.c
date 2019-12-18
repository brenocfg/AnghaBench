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
struct TYPE_2__ {int /*<<< orphan*/ * cfunc; } ;
struct cmd_list_element {TYPE_1__ function; int /*<<< orphan*/ * func; } ;
typedef  int /*<<< orphan*/  cmd_cfunc_ftype ;

/* Variables and functions */
 int /*<<< orphan*/ * do_cfunc ; 

void
set_cmd_cfunc (struct cmd_list_element *cmd, cmd_cfunc_ftype *cfunc)
{
  if (cfunc == NULL)
    cmd->func = NULL;
  else
    cmd->func = do_cfunc;
  cmd->function.cfunc = cfunc; /* Ok.  */
}