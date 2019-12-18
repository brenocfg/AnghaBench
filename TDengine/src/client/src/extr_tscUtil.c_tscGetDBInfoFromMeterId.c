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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 

void tscGetDBInfoFromMeterId(char* meterId, char* db) {
  char* st = strstr(meterId, TS_PATH_DELIMITER);
  if (st != NULL) {
    char* end = strstr(st + 1, TS_PATH_DELIMITER);
    if (end != NULL) {
      memcpy(db, meterId, (end - meterId));
      db[end - meterId] = 0;
      return;
    }
  }

  db[0] = 0;
}