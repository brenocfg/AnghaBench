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
struct TYPE_2__ {size_t team_id; scalar_t__ static_trip; scalar_t__ work_share_generation; int /*<<< orphan*/ * work_share; struct gomp_team* team; } ;
struct gomp_thread_start_data {void (* fn ) (void*) ;scalar_t__ nested; TYPE_1__ ts; void* fn_data; } ;
struct gomp_thread {void (* fn ) (void*) ;int /*<<< orphan*/ * data; TYPE_1__ ts; int /*<<< orphan*/  release; } ;
struct gomp_team {int /*<<< orphan*/  barrier; int /*<<< orphan*/ ** ordered_release; } ;

/* Variables and functions */
 int /*<<< orphan*/  gomp_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gomp_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct gomp_thread** gomp_threads ; 
 int /*<<< orphan*/  gomp_threads_dock ; 
 struct gomp_thread gomp_tls_data ; 
 int /*<<< orphan*/  gomp_tls_key ; 
 int /*<<< orphan*/  pthread_setspecific (int /*<<< orphan*/ ,struct gomp_thread*) ; 

__attribute__((used)) static void *
gomp_thread_start (void *xdata)
{
  struct gomp_thread_start_data *data = xdata;
  struct gomp_thread *thr;
  void (*local_fn) (void *);
  void *local_data;

#ifdef HAVE_TLS
  thr = &gomp_tls_data;
#else
  struct gomp_thread local_thr;
  thr = &local_thr;
  pthread_setspecific (gomp_tls_key, thr);
#endif
  gomp_sem_init (&thr->release, 0);

  /* Extract what we need from data.  */
  local_fn = data->fn;
  local_data = data->fn_data;
  thr->ts = data->ts;

  thr->ts.team->ordered_release[thr->ts.team_id] = &thr->release;

  if (data->nested)
    {
      gomp_barrier_wait (&thr->ts.team->barrier);
      local_fn (local_data);
      gomp_barrier_wait (&thr->ts.team->barrier);
    }
  else
    {
      gomp_threads[thr->ts.team_id] = thr;

      gomp_barrier_wait (&gomp_threads_dock);
      do
	{
	  struct gomp_team *team;

	  local_fn (local_data);

	  /* Clear out the team and function data.  This is a debugging
	     signal that we're in fact back in the dock.  */
	  team = thr->ts.team;
	  thr->fn = NULL;
	  thr->data = NULL;
	  thr->ts.team = NULL;
	  thr->ts.work_share = NULL;
	  thr->ts.team_id = 0;
	  thr->ts.work_share_generation = 0;
	  thr->ts.static_trip = 0;

	  gomp_barrier_wait (&team->barrier);
	  gomp_barrier_wait (&gomp_threads_dock);

	  local_fn = thr->fn;
	  local_data = thr->data;
	}
      while (local_fn);
    }

  return NULL;
}