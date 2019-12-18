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
struct TYPE_4__ {TYPE_1__* threads; scalar_t__ task; } ;
struct TYPE_3__ {int tid; } ;

/* Variables and functions */
 TYPE_2__* current_inferior ; 
 int next_thread_id ; 

__attribute__((used)) static int
inf_pick_first_thread (void)
{
  if (current_inferior->task && current_inferior->threads)
    /* The first thread.  */
    return current_inferior->threads->tid;
  else
    /* What may be the next thread.  */
    return next_thread_id;
}