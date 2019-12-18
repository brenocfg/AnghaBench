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
struct tm {int tm_year; } ;

/* Variables and functions */
 int /*<<< orphan*/  adjhour (struct tm*,char,int,int /*<<< orphan*/ ) ; 
 int mktime (struct tm*) ; 

__attribute__((used)) static int
domktime(struct tm *t, char type)
{
  time_t ret;

  while ((ret = mktime(t)) == -1 && t->tm_year > 68 && t->tm_year < 138)
    /* While mktime() fails, adjust by an hour */
    adjhour(t, type == '-' ? type : '+', 1, 0);

  return ret;
}