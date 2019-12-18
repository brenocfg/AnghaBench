#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int integer; } ;
struct continuation_arg {TYPE_5__* next; TYPE_1__ data; } ;
struct TYPE_7__ {int integer; } ;
struct TYPE_10__ {TYPE_4__* next; TYPE_2__ data; } ;
struct TYPE_8__ {int integer; } ;
struct TYPE_9__ {TYPE_3__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_CLEANUPS ; 
 int /*<<< orphan*/  do_exec_cleanups (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  step_once (int,int,int) ; 
 scalar_t__ stop_step ; 

__attribute__((used)) static void
step_1_continuation (struct continuation_arg *arg)
{
  int count;
  int skip_subroutines;
  int single_inst;

  skip_subroutines = arg->data.integer;
  single_inst      = arg->next->data.integer;
  count            = arg->next->next->data.integer;

  if (stop_step)
    step_once (skip_subroutines, single_inst, count - 1);
  else
    if (!single_inst || skip_subroutines)
      do_exec_cleanups (ALL_CLEANUPS);
}