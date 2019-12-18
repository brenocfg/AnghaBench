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
struct mf_thread_data {int state; } ;
typedef  enum __mf_state_enum { ____Placeholder___mf_state_enum } __mf_state_enum ;

/* Variables and functions */
 struct mf_thread_data* __mf_find_threadinfo (int /*<<< orphan*/ ) ; 
 int reentrant ; 

enum __mf_state_enum
__mf_get_state (void)
{
  struct mf_thread_data *data = __mf_find_threadinfo (0);
  if (data)
    return data->state;

  /* If we've never seen this thread before, consider it to be in the
     reentrant state.  The state gets reset to active for the main thread
     in __mf_init, and for child threads in __mf_pthread_spawner.

     The trickiest bit here is that the LinuxThreads pthread_manager thread
     should *always* be considered to be reentrant, so that none of our 
     hooks actually do anything.  Why?  Because that thread isn't a real
     thread from the point of view of the thread library, and so lots of
     stuff isn't initialized, leading to SEGV very quickly.  Even calling
     pthread_self is a bit suspect, but it happens to work.  */

  return reentrant;
}