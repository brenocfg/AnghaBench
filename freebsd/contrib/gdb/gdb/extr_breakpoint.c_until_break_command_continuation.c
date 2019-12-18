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
struct TYPE_2__ {scalar_t__ pointer; } ;
struct continuation_arg {TYPE_1__ data; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_exec_cleanups (struct cleanup*) ; 

__attribute__((used)) static void
until_break_command_continuation (struct continuation_arg *arg)
{
  struct cleanup *cleanups;

  cleanups = (struct cleanup *) arg->data.pointer;
  do_exec_cleanups (cleanups);
}