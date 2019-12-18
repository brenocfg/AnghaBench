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
typedef  int /*<<< orphan*/  db ;
typedef  int /*<<< orphan*/  SDbObj ;

/* Variables and functions */
 int TSDB_METER_ID_LEN ; 
 int /*<<< orphan*/  TS_PATH_DELIMITER ; 
 int /*<<< orphan*/  dbSdb ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sdbGetRow (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 char* strstr (char*,int /*<<< orphan*/ ) ; 

SDbObj *mgmtGetDbByMeterId(char *meterId) {
  char db[TSDB_METER_ID_LEN], *pos;

  pos = strstr(meterId, TS_PATH_DELIMITER);
  pos = strstr(pos + 1, TS_PATH_DELIMITER);
  memset(db, 0, sizeof(db));
  strncpy(db, meterId, pos - meterId);

  return (SDbObj *)sdbGetRow(dbSdb, db);
}