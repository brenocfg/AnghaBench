#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct value {int dummy; } ;
struct task_entry {void* task_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CURRENT_THREAD () ; 
 struct task_entry* get_thread_entry_vptr (int /*<<< orphan*/ ) ; 
 scalar_t__ thread_support ; 

void *
get_self_id (void)
{
  struct value *val;
  void *self_id;
  int result;
  struct task_entry *ent;
  extern int do_not_insert_breakpoints;

#if !((defined(sun) && defined(__SVR4)) || defined(VXWORKS_TARGET) || defined(__WIN32__))
  if (thread_support)
#endif
    {
      ent = get_thread_entry_vptr (GET_CURRENT_THREAD ());
      return ent ? ent->task_id : 0;
    }

  /* FIXME: calling a function in the inferior with a multithreaded application
     is not reliable, so return NULL if there is no safe way to get the current
     task */
  return NULL;
}