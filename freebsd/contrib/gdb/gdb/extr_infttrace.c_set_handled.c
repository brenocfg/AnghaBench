#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int handled; } ;
typedef  TYPE_1__ thread_info ;
typedef  int /*<<< orphan*/  lwpid_t ;

/* Variables and functions */
 TYPE_1__* add_tthread (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* find_thread_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_handled (int pid, lwpid_t tid)
{
  thread_info *p;

  p = find_thread_info (tid);
  if (NULL == p)
    p = add_tthread (pid, tid);

  p->handled = 1;
}