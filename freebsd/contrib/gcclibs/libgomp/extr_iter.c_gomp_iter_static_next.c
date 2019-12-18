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
struct gomp_work_share {long next; long end; scalar_t__ chunk_size; int incr; } ;
struct TYPE_2__ {int static_trip; unsigned long team_id; struct gomp_work_share* work_share; struct gomp_team* team; } ;
struct gomp_thread {TYPE_1__ ts; } ;
struct gomp_team {int nthreads; } ;

/* Variables and functions */
 struct gomp_thread* gomp_thread () ; 

int
gomp_iter_static_next (long *pstart, long *pend)
{
  struct gomp_thread *thr = gomp_thread ();
  struct gomp_team *team = thr->ts.team;
  struct gomp_work_share *ws = thr->ts.work_share;
  unsigned long nthreads = team ? team->nthreads : 1;

  if (thr->ts.static_trip == -1)
    return -1;

  /* Quick test for degenerate teams and orphaned constructs.  */
  if (nthreads == 1)
    {
      *pstart = ws->next;
      *pend = ws->end;
      thr->ts.static_trip = -1;
      return ws->next == ws->end;
    }

  /* We interpret chunk_size zero as "unspecified", which means that we
     should break up the iterations such that each thread makes only one
     trip through the outer loop.  */
  if (ws->chunk_size == 0)
    {
      unsigned long n, q, i;
      unsigned long s0, e0;
      long s, e;

      if (thr->ts.static_trip > 0)
	return 1;

      /* Compute the total number of iterations.  */
      s = ws->incr + (ws->incr > 0 ? -1 : 1);
      n = (ws->end - ws->next + s) / ws->incr;
      i = thr->ts.team_id;

      /* Compute the "zero-based" start and end points.  That is, as
         if the loop began at zero and incremented by one.  */
      q = n / nthreads;
      q += (q * nthreads != n);
      s0 = q * i;
      e0 = s0 + q;
      if (e0 > n)
        e0 = n;

      /* Notice when no iterations allocated for this thread.  */
      if (s0 >= e0)
	{
	  thr->ts.static_trip = 1;
	  return 1;
	}

      /* Transform these to the actual start and end numbers.  */
      s = (long)s0 * ws->incr + ws->next;
      e = (long)e0 * ws->incr + ws->next;

      *pstart = s;
      *pend = e;
      thr->ts.static_trip = (e0 == n ? -1 : 1);
      return 0;
    }
  else
    {
      unsigned long n, s0, e0, i, c;
      long s, e;

      /* Otherwise, each thread gets exactly chunk_size iterations
	 (if available) each time through the loop.  */

      s = ws->incr + (ws->incr > 0 ? -1 : 1);
      n = (ws->end - ws->next + s) / ws->incr;
      i = thr->ts.team_id;
      c = ws->chunk_size;

      /* Initial guess is a C sized chunk positioned nthreads iterations
	 in, offset by our thread number.  */
      s0 = (thr->ts.static_trip * nthreads + i) * c;
      e0 = s0 + c;

      /* Detect overflow.  */
      if (s0 >= n)
	return 1;
      if (e0 > n)
	e0 = n;

      /* Transform these to the actual start and end numbers.  */
      s = (long)s0 * ws->incr + ws->next;
      e = (long)e0 * ws->incr + ws->next;

      *pstart = s;
      *pend = e;

      if (e0 == n)
	thr->ts.static_trip = -1;
      else
	thr->ts.static_trip++;
      return 0;
    }
}