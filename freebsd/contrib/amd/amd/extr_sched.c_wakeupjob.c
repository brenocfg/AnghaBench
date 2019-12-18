#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hdr; } ;
typedef  TYPE_1__ pjob ;

/* Variables and functions */
 int /*<<< orphan*/  ins_que (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_list_head ; 
 int /*<<< orphan*/  rem_que (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_notify_todo ; 

__attribute__((used)) static void
wakeupjob(pjob *p)
{
  rem_que(&p->hdr);
  ins_que(&p->hdr, &proc_list_head);
  task_notify_todo++;
}