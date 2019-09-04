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
 int /*<<< orphan*/  printf (char*,double,double) ; 

__attribute__((used)) static int progress_callback(void *clientp, double dltotal,
                             double dlnow, double ultotal, double ulnow)
{
  (void)clientp;
  (void)ulnow;
  (void)ultotal;

  if((dltotal > 0.0) && (dlnow > dltotal)) {
    /* this should not happen with test case 599 */
    printf("%.0f > %.0f !!\n", dltotal, dlnow);
    return -1;
  }

  return 0;
}