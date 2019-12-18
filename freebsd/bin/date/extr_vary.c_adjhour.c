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
struct tm {int tm_hour; } ;

/* Variables and functions */
 int /*<<< orphan*/  adjday (struct tm*,char,int,int /*<<< orphan*/ ) ; 
 int domktime (struct tm*,char) ; 

__attribute__((used)) static int
adjhour(struct tm *t, char type, int val, int mk)
{
  if (val < 0)
    return 0;

  switch (type) {
    case '+':
      if (val) {
        int days;

        days = (t->tm_hour + val) / 24;
        val %= 24;
        t->tm_hour += val;
        t->tm_hour %= 24;
        if (!adjday(t, '+', days, 0))
          return 0;
      }
      break;

    case '-':
      if (val) {
        int days;

        days = val / 24;
        val %= 24;
        if (val > t->tm_hour) {
          days++;
          val -= 24;
        }
        t->tm_hour -= val;
        if (!adjday(t, '-', days, 0))
          return 0;
      }
      break;

    default:
      if (val > 23)
        return 0;
      t->tm_hour = val;
  }

  return !mk || domktime(t, type) != -1;
}