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
struct TYPE_3__ {scalar_t__ cfgStatus; } ;
typedef  TYPE_1__ SGlobalConfig ;

/* Variables and functions */
 scalar_t__ TSDB_CFG_CSTATUS_DEFAULT ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  pPrint (char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 
 TYPE_1__* tsGetConfigOption (char*) ; 
 int /*<<< orphan*/  tsTimezone ; 

void taosGetSystemTimezone() {
  // get and set default timezone
  SGlobalConfig *cfg_timezone = tsGetConfigOption("timezone");
  if (cfg_timezone && cfg_timezone->cfgStatus < TSDB_CFG_CSTATUS_DEFAULT) {
    char *tz = getenv("TZ");
    if (tz == NULL || strlen(tz) == 0) {
      strcpy(tsTimezone, "not configured");
    }
    else {
      strcpy(tsTimezone, tz);
    }
    cfg_timezone->cfgStatus = TSDB_CFG_CSTATUS_DEFAULT;
    pPrint("timezone not configured, use default");
  }
}