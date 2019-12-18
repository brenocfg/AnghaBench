#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* stepping_mode; struct TYPE_4__* next; } ;
typedef  TYPE_1__ thread_info ;
struct TYPE_6__ {TYPE_1__* head; } ;
struct TYPE_5__ {TYPE_1__* head; } ;

/* Variables and functions */
 void* DO_DEFAULT ; 
 scalar_t__ debug_on ; 
 TYPE_3__ deleted_threads ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_2__ thread_head ; 

__attribute__((used)) static void
clear_all_stepping_mode (void)
{
  thread_info *p;

#ifdef WAIT_BUFFER_DEBUG
  if (debug_on)
    printf ("clear_all_stepping_mode\n");
#endif

  for (p = thread_head.head; p; p = p->next)
    {
      p->stepping_mode = DO_DEFAULT;
    }

  for (p = deleted_threads.head; p; p = p->next)
    {
      p->stepping_mode = DO_DEFAULT;
    }
}