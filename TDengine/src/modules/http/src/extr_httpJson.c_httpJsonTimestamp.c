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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  JsonBuf ;

/* Variables and functions */
 int /*<<< orphan*/  httpJsonString (int /*<<< orphan*/ *,char*,int) ; 
 struct tm* localtime (int*) ; 
 scalar_t__ snprintf (char*,int,char*,int) ; 
 scalar_t__ strftime (char*,int,char*,struct tm*) ; 

void httpJsonTimestamp(JsonBuf* buf, int64_t t, bool us) {
  char ts[35] = {0};
  struct tm *ptm;
  int precision = 1000;
  if (us) {
    precision = 1000000;
  }

  time_t tt = t / precision;
  ptm = localtime(&tt);
  int length = (int) strftime(ts, 35, "%Y-%m-%d %H:%M:%S", ptm);
  if (us) {
    length += snprintf(ts + length, 8, ".%06ld", t % precision);
  } else {
    length += snprintf(ts + length, 5, ".%03ld", t % precision);
  }

  httpJsonString(buf, ts, length);
}