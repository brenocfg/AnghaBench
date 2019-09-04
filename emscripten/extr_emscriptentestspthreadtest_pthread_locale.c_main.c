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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_test () ; 
 int /*<<< orphan*/  emscripten_has_threading_support () ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  thread_test ; 

int main (int argc, char *argv[])
{
  puts("Doing test in main thread");
  locale_t main_loc = do_test();
  locale_t child_loc;

  if (!emscripten_has_threading_support())
  {
    child_loc = main_loc;
  }
  else
  {
    long id = 1;
    pthread_t thread;

    pthread_create(&thread, NULL, thread_test, (void *)id);

    pthread_join(thread, (void**)&child_loc);
  }

#ifdef REPORT_RESULT
  int result = (main_loc == child_loc);
  REPORT_RESULT(result);
#endif

  pthread_exit(NULL);
}