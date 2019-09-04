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
typedef  int /*<<< orphan*/  tm ;
struct tm {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; int tm_wday; int tm_yday; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tm*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * strptime (char*,char*,struct tm*) ; 

int main() {
  int result = 0;
  struct tm tm;

  memset(&tm, 0xaa, sizeof(tm));

  /* Test we don't crash on uninitialized struct tm.
     Some fields might contain bogus values until everything
     needed is initialized, but we shouldn't crash.  */
  if (strptime("2007", "%Y", &tm) == NULL ||
      strptime("12", "%d", &tm) == NULL || strptime("Feb", "%b", &tm) == NULL ||
      strptime("13", "%M", &tm) == NULL || strptime("21", "%S", &tm) == NULL ||
      strptime("16", "%H", &tm) == NULL) {
    printf("ERR: returned NULL");
    exit(EXIT_FAILURE);
  }

  if (tm.tm_sec != 21 || tm.tm_min != 13 || tm.tm_hour != 16 ||
      tm.tm_mday != 12 || tm.tm_mon != 1 || tm.tm_year != 107 ||
      tm.tm_wday != 1 || tm.tm_yday != 42) {
    printf("ERR: unexpected tm content (1) - %d/%d/%d %d:%d:%d", tm.tm_mon + 1,
           tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    exit(EXIT_FAILURE);
  }

  if (strptime("8", "%d", &tm) == NULL) {
    printf("ERR: strptime failed");
    exit(EXIT_FAILURE);
  }

  if (tm.tm_sec != 21 || tm.tm_min != 13 || tm.tm_hour != 16 ||
      tm.tm_mday != 8 || tm.tm_mon != 1 || tm.tm_year != 107 ||
      tm.tm_wday != 4 || tm.tm_yday != 38) {
    printf("ERR: unexpected tm content (2) - %d/%d/%d %d:%d:%d", tm.tm_mon + 1,
           tm.tm_mday, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    exit(EXIT_FAILURE);
  }

  printf("OK");
}