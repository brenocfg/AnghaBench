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

/* Variables and functions */
 int /*<<< orphan*/  TS_PATH_DELIMITER ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 

void mgmtGetAcctStr(char *src, char *dest) {
  char *pos = strstr(src, TS_PATH_DELIMITER);
  while ((pos != NULL) && (*src != *pos)) {
    *dest = *src;
    src++;
    dest++;
  }

  *dest = 0;
}