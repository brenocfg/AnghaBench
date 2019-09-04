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
struct tm {int tm_wday; int tm_mon; int tm_mday; int tm_year; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  ReadMonth (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strptime (char*,char*,struct tm*) ; 

int main() {
  struct tm tm;
  char *ptr = strptime("17410105012000", "%H%M%S%d%m%Y", &tm);

  printf(
      "%s: %s, %d/%d/%d %d:%d:%d", (ptr != NULL && *ptr == '\0') ? "OK" : "ERR",
      tm.tm_wday == 0
          ? "Sun"
          : (tm.tm_wday == 1
                 ? "Mon"
                 : (tm.tm_wday == 2
                        ? "Tue"
                        : (tm.tm_wday == 3
                               ? "Wed"
                               : (tm.tm_wday == 4
                                      ? "Thu"
                                      : (tm.tm_wday == 5
                                             ? "Fri"
                                             : (tm.tm_wday == 6 ? "Sat"
                                                                : "ERR")))))),
      tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min,
      tm.tm_sec);

  printf("\n");

  ReadMonth("jan");
  ReadMonth("january");
  ReadMonth("feb");
  ReadMonth("february");
  ReadMonth("march");
  ReadMonth("mar");
  ReadMonth("april");
  ReadMonth("may");
  ReadMonth("may");
  ReadMonth("june");
  ReadMonth("jul");
  ReadMonth("august");
  ReadMonth("september");
  ReadMonth("oct");
  ReadMonth("nov");
  ReadMonth("november");
  ReadMonth("december");

  return 0;
}