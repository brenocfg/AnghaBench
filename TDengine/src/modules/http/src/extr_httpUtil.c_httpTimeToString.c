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
struct tm {int dummy; } ;

/* Variables and functions */
 struct tm* localtime (int*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 

void httpTimeToString(time_t t, char *buf, int buflen) {
  memset(buf, 0, (size_t)buflen);
  char ts[30] = {0};

  struct tm *ptm;
  time_t     tt = t / 1000;
  ptm = localtime(&tt);
  strftime(ts, 64, "%Y-%m-%d %H:%M:%S", ptm);
  sprintf(buf, "%s.%03ld", ts, t % 1000);
}