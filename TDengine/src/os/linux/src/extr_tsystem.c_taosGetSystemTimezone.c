#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {scalar_t__ cfgStatus; } ;
typedef  TYPE_1__ SGlobalConfig ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ MILLISECOND_PER_HOUR ; 
 scalar_t__ MILLISECOND_PER_SECOND ; 
 scalar_t__ TSDB_CFG_CSTATUS_DEFAULT ; 
 int /*<<< orphan*/  abs (scalar_t__) ; 
 size_t daylight ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  pPrint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 scalar_t__ timezone ; 
 TYPE_1__* tsGetConfigOption (char*) ; 
 int /*<<< orphan*/  tsTimezone ; 
 char** tzname ; 
 int /*<<< orphan*/  tzset () ; 

void taosGetSystemTimezone() {
  SGlobalConfig *cfg_timezone = tsGetConfigOption("timezone");
  if (cfg_timezone == NULL) return;
  if (cfg_timezone->cfgStatus >= TSDB_CFG_CSTATUS_DEFAULT) {
    return;
  }

  /*
   * NOTE: do not remove it.
   * Enforce set the correct daylight saving time(DST) flag according
   * to current time
   */
  time_t    tx1 = time(NULL);
  struct tm tm1;
  localtime_r(&tx1, &tm1);

  /* load time zone string from /etc/timezone */
  FILE *f = fopen("/etc/timezone", "r");
  char  buf[64] = {0};
  if (f != NULL) {
    fread(buf, 64, 1, f);
    fclose(f);
  }

  char *lineEnd = strstr(buf, "\n");
  if (lineEnd != NULL) {
    *lineEnd = 0;
  }

  // for CentOS system, /etc/timezone does not exist. Ignore the TZ environment variables
  if (strlen(buf) > 0) {
    setenv("TZ", buf, 1);
  }

  // get and set default timezone
  tzset();

  /*
   * get CURRENT time zone.
   * system current time zone is affected by daylight saving time(DST)
   *
   * e.g., the local time zone of London in DST is GMT+01:00,
   * otherwise is GMT+00:00
   */
  int32_t tz = (-timezone * MILLISECOND_PER_SECOND) / MILLISECOND_PER_HOUR;
  tz += daylight;

  /*
   * format example:
   *
   * Asia/Shanghai   (CST, +0800)
   * Europe/London   (BST, +0100)
   */
  sprintf(tsTimezone, "%s (%s, %s%02d00)", buf, tzname[daylight], tz >= 0 ? "+" : "-", abs(tz));

  cfg_timezone->cfgStatus = TSDB_CFG_CSTATUS_DEFAULT;
  pPrint("timezone not configured, set to system default:%s", tsTimezone);
}