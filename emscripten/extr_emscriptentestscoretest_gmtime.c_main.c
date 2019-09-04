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
typedef  int time_t ;
struct tm {int tm_hour; int tm_yday; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 struct tm* gmtime (int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int time (int /*<<< orphan*/ *) ; 

int main(void) {
  time_t t = time(NULL);
  struct tm *ptm = gmtime(&t);
  struct tm tmCurrent = *ptm;
  int hour = tmCurrent.tm_hour;

  t -= hour * 3600;  // back to midnight
  int yday = -1;
  for (hour = 0; hour < 24; hour++) {
    ptm = gmtime(&t);
    // tm_yday must be constant all day...
    printf("yday: %d, hour: %d\n", ptm->tm_yday, hour);
    if (yday == -1)
      yday = ptm->tm_yday;
    else
      assert(yday == ptm->tm_yday);
    t += 3600;  // add one hour
  }
  printf("ok!\n");
  return (0);
}