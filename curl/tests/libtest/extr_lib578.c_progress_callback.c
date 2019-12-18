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
 size_t data_size ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  libtest_arg2 ; 

__attribute__((used)) static int progress_callback(void *clientp, double dltotal, double dlnow,
                             double ultotal, double ulnow)
{
  FILE *moo = fopen(libtest_arg2, "wb");

  (void)clientp; /* UNUSED */
  (void)dltotal; /* UNUSED */
  (void)dlnow; /* UNUSED */

  if(moo) {
    if((size_t)ultotal == data_size && (size_t)ulnow == data_size)
      fprintf(moo, "PASSED, UL data matched data size\n");
    else
      fprintf(moo, "Progress callback called with UL %f out of %f\n",
              ulnow, ultotal);
    fclose(moo);
  }
  return 0;
}