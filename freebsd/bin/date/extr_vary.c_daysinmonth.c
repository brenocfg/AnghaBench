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
struct tm {int tm_year; int tm_mon; } ;

/* Variables and functions */
 int* mdays ; 

__attribute__((used)) static int
daysinmonth(const struct tm *t)
{
  int year;

  year = t->tm_year + 1900;

  if (t->tm_mon == 1)
    if (!(year % 400))
      return 29;
    else if (!(year % 100))
      return 28;
    else if (!(year % 4))
      return 29;
    else
      return 28;
  else if (t->tm_mon >= 0 && t->tm_mon < 12)
    return mdays[t->tm_mon];

  return 0;
}