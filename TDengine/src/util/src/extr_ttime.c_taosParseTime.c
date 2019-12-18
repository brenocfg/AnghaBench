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
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  parseLocaltime (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parseTimeWithTz (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strnchr (char*,char,int /*<<< orphan*/ ,int) ; 

int32_t taosParseTime(char* timestr, int64_t* time, int32_t len, int32_t timePrec) {
  /* parse datatime string in with tz */
  if (strnchr(timestr, 'T', len, false) != NULL) {
    return parseTimeWithTz(timestr, time, timePrec);
  } else {
    return parseLocaltime(timestr, time, timePrec);
  }
}