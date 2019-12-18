#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t int32_t ;
struct TYPE_4__ {size_t n; int /*<<< orphan*/  z; } ;
typedef  TYPE_1__ SSQLToken ;

/* Variables and functions */
 size_t TSDB_CODE_INVALID_SQL ; 
 size_t TSDB_CODE_SUCCESS ; 
 size_t TSDB_DB_NAME_LEN ; 
 size_t TSDB_METER_ID_LEN ; 
 size_t TSDB_METER_NAME_LEN ; 
 char* TS_PATH_DELIMITER ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 
 size_t tListLen (char*) ; 

__attribute__((used)) static int32_t setObjFullName(char* fullName, char* account, SSQLToken* pDB, SSQLToken* tableName, int32_t* xlen) {
  int32_t totalLen = 0;

  if (account != NULL) {
    int32_t len = strlen(account);
    strcpy(fullName, account);
    fullName[len] = TS_PATH_DELIMITER[0];
    totalLen += (len + 1);
  }

  /* db name is not specified, the tableName dose not include db name */
  if (pDB != NULL) {
    if (pDB->n > TSDB_DB_NAME_LEN) {
      return TSDB_CODE_INVALID_SQL;
    }

    memcpy(&fullName[totalLen], pDB->z, pDB->n);
    totalLen += pDB->n;
  }

  if (tableName != NULL) {
    if (pDB != NULL) {
      fullName[totalLen] = TS_PATH_DELIMITER[0];
      totalLen += 1;

      /* here we only check the table name length limitation */
      if (tableName->n > TSDB_METER_NAME_LEN) {
        return TSDB_CODE_INVALID_SQL;
      }
    } else {  // pDB == NULL, the db prefix name is specified in tableName
      /* the length limitation includes tablename + dbname + sep */
      if (tableName->n > TSDB_METER_NAME_LEN + TSDB_DB_NAME_LEN + tListLen(TS_PATH_DELIMITER)) {
        return TSDB_CODE_INVALID_SQL;
      }
    }

    memcpy(&fullName[totalLen], tableName->z, tableName->n);
    totalLen += tableName->n;
  }

  if (xlen != NULL) {
    *xlen = totalLen;
  }

  if (totalLen < TSDB_METER_ID_LEN) {
    fullName[totalLen] = 0;
  }

  return (totalLen <= TSDB_METER_ID_LEN) ? TSDB_CODE_SUCCESS : TSDB_CODE_INVALID_SQL;
}