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

/* Variables and functions */
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int getloadavg (double*,int) ; 
 unsigned int gomp_nthreads_var ; 
 unsigned int sysconf (int /*<<< orphan*/ ) ; 

unsigned
gomp_dynamic_max_threads (void)
{
  unsigned n_onln, loadavg;

#ifdef _SC_NPROCESSORS_ONLN
  n_onln = sysconf (_SC_NPROCESSORS_ONLN);
  if (n_onln > gomp_nthreads_var)
    n_onln = gomp_nthreads_var;
#else
  n_onln = gomp_nthreads_var;
#endif

  loadavg = 0;
#ifdef HAVE_GETLOADAVG
  {
    double dloadavg[3];
    if (getloadavg (dloadavg, 3) == 3)
      {
	/* Add 0.1 to get a kind of biased rounding.  */
	loadavg = dloadavg[2] + 0.1;
      }
  }
#endif

  if (loadavg >= n_onln)
    return 1;
  else
    return n_onln - loadavg;
}