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
struct tm {int tm_year; } ;

/* Variables and functions */
 int domktime (struct tm*,char) ; 

__attribute__((used)) static int
adjyear(struct tm *t, char type, int val, int mk)
{
  switch (type) {
    case '+':
      t->tm_year += val;
      break;
    case '-':
      t->tm_year -= val;
      break;
    default:
      t->tm_year = val;
      if (t->tm_year < 69)
      	t->tm_year += 100;		/* as per date.c */
      else if (t->tm_year > 1900)
        t->tm_year -= 1900;             /* struct tm holds years since 1900 */
      break;
  }
  return !mk || domktime(t, type) != -1;
}