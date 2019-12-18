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
struct TYPE_3__ {scalar_t__ have_signal; struct TYPE_3__* next; } ;
typedef  TYPE_1__ thread_info ;
struct TYPE_4__ {TYPE_1__* head; } ;

/* Variables and functions */
 TYPE_2__ thread_head ; 

__attribute__((used)) static int
saved_signals_exist (void)
{
  thread_info *p;

  for (p = thread_head.head; p; p = p->next)
    {
      if (p->have_signal)
	{
	  return 1;
	}
    }

  return 0;
}