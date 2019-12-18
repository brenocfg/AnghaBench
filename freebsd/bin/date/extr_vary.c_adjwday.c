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
struct tm {int tm_wday; } ;

/* Variables and functions */
 int adjday (struct tm*,char,int,int) ; 

__attribute__((used)) static int
adjwday(struct tm *t, char type, int val, int istext, int mk)
{
  if (val < 0)
    return 0;

  switch (type) {
    case '+':
      if (istext)
        if (val < t->tm_wday)
          val = 7 - t->tm_wday + val;  /* early next week */
        else
          val -= t->tm_wday;           /* later this week */
      else
        val *= 7;                      /* "-v+5w" == "5 weeks in the future" */
      return !val || adjday(t, '+', val, mk);
    case '-':
      if (istext) {
        if (val > t->tm_wday)
          val = 7 - val + t->tm_wday;  /* later last week */
        else
          val = t->tm_wday - val;      /* early this week */
      } else
        val *= 7;                      /* "-v-5w" == "5 weeks ago" */
      return !val || adjday(t, '-', val, mk);
    default:
      if (val < t->tm_wday)
        return adjday(t, '-', t->tm_wday - val, mk);
      else if (val > 6)
        return 0;
      else if (val > t->tm_wday)
        return adjday(t, '+', val - t->tm_wday, mk);
  }
  return 1;
}