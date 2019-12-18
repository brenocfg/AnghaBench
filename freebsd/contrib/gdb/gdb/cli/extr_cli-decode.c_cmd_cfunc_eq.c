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
struct TYPE_2__ {void (* cfunc ) (char*,int) ;} ;
struct cmd_list_element {scalar_t__ func; TYPE_1__ function; } ;

/* Variables and functions */
 scalar_t__ do_cfunc ; 

int
cmd_cfunc_eq (struct cmd_list_element *cmd,
	      void (*cfunc) (char *args, int from_tty))
{
  return cmd->func == do_cfunc && cmd->function.cfunc == cfunc;
}