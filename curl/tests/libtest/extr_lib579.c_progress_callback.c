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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  libtest_arg2 ; 

__attribute__((used)) static int progress_callback(void *clientp, double dltotal, double dlnow,
                             double ultotal, double ulnow)
{
  static int prev_ultotal = -1;
  static int prev_ulnow = -1;
  (void)clientp; /* UNUSED */
  (void)dltotal; /* UNUSED */
  (void)dlnow; /* UNUSED */

  /* to avoid depending on timing, which will cause this progress function to
     get called a different number of times depending on circumstances, we
     only log these lines if the numbers are different from the previous
     invoke */
  if((prev_ultotal != (int)ultotal) ||
     (prev_ulnow != (int)ulnow)) {

    FILE *moo = fopen(libtest_arg2, "ab");
    if(moo) {
      fprintf(moo, "Progress callback called with UL %d out of %d\n",
              (int)ulnow, (int)ultotal);
      fclose(moo);
    }
    prev_ulnow = (int) ulnow;
    prev_ultotal = (int) ultotal;
  }
  return 0;
}