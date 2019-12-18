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
struct tm {int tm_mon; int tm_mday; } ;

/* Variables and functions */
 int /*<<< orphan*/  adjyear (struct tm*,char,int,int /*<<< orphan*/ ) ; 
 int daysinmonth (struct tm*) ; 
 int domktime (struct tm*,char) ; 

__attribute__((used)) static int
adjmon(struct tm *t, char type, int val, int istext, int mk)
{
  int lmdays;

  if (val < 0)
    return 0;

  switch (type) {
    case '+':
      if (istext) {
        if (val <= t->tm_mon)
          val += 11 - t->tm_mon;	/* early next year */
        else
          val -= t->tm_mon + 1;		/* later this year */
      }
      if (val) {
        if (!adjyear(t, '+', (t->tm_mon + val) / 12, 0))
          return 0;
        val %= 12;
        t->tm_mon += val;
        if (t->tm_mon > 11)
          t->tm_mon -= 12;
      }
      break;

    case '-':
      if (istext) {
        if (val-1 > t->tm_mon)
          val = 13 - val + t->tm_mon;	/* later last year */
        else
          val = t->tm_mon - val + 1;	/* early this year */
      }
      if (val) {
        if (!adjyear(t, '-', val / 12, 0))
          return 0;
        val %= 12;
        if (val > t->tm_mon) {
          if (!adjyear(t, '-', 1, 0))
            return 0;
          val -= 12;
        }
        t->tm_mon -= val;
      }
      break;

    default:
      if (val > 12 || val < 1)
        return 0;
      t->tm_mon = --val;
  }

  /* e.g., -v-1m on March, 31 is the last day of February in common sense */
  lmdays = daysinmonth(t);
  if (t->tm_mday > lmdays)
    t->tm_mday = lmdays;

  return !mk || domktime(t, type) != -1;
}