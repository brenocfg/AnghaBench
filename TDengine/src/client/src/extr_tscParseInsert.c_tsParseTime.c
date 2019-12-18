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
typedef  int int64_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ int16_t ;
struct TYPE_4__ {scalar_t__ type; char* z; int n; } ;
typedef  TYPE_1__ SSQLToken ;

/* Variables and functions */
 scalar_t__ TK_INTEGER ; 
 scalar_t__ TK_MINUS ; 
 scalar_t__ TK_NOW ; 
 scalar_t__ TK_PLUS ; 
 int TSDB_CODE_INVALID_SQL ; 
 scalar_t__ TSDB_CODE_SUCCESS ; 
 scalar_t__ TSDB_TIME_PRECISION_MILLI ; 
 scalar_t__ getTimestampInUsFromStr (char*,int,int*) ; 
 int str2int64 (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 TYPE_1__ tStrGetToken (char*,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int taosGetTimestamp (scalar_t__) ; 
 scalar_t__ taosParseTime (char*,int*,int,scalar_t__) ; 

int tsParseTime(SSQLToken *pToken, int64_t *time, char **next, char *error, int16_t timePrec) {
  char *    token;
  int       tokenlen;
  int32_t   index = 0;
  SSQLToken sToken;
  int64_t   interval;
  int64_t   useconds = 0;
  char *    pTokenEnd = *next;

  index = 0;

  if (pToken->type == TK_NOW) {
    useconds = taosGetTimestamp(timePrec);
  } else if (strncmp(pToken->z, "0", 1) == 0 && pToken->n == 1) {
    // do nothing
  } else if (pToken->type == TK_INTEGER) {
    useconds = str2int64(pToken->z);
  } else {
    // strptime("2001-11-12 18:31:01", "%Y-%m-%d %H:%M:%S", &tm);
    if (taosParseTime(pToken->z, time, pToken->n, timePrec) != TSDB_CODE_SUCCESS) {
      return TSDB_CODE_INVALID_SQL;
    }

    return TSDB_CODE_SUCCESS;
  }

  for (int k = pToken->n; pToken->z[k] != '\0'; k++) {
    if (pToken->z[k] == ' ' || pToken->z[k] == '\t') continue;
    if (pToken->z[k] == ',') {
      *next = pTokenEnd;
      *time = useconds;
      return 0;
    }

    break;
  }

  /*
   * time expression:
   * e.g., now+12a, now-5h
   */
  SSQLToken valueToken;
  index = 0;
  sToken = tStrGetToken(pTokenEnd, &index, false, 0, NULL);
  pTokenEnd += index;
  if (sToken.type == TK_MINUS || sToken.type == TK_PLUS) {
    index = 0;
    valueToken = tStrGetToken(pTokenEnd, &index, false, 0, NULL);
    pTokenEnd += index;
    if (valueToken.n < 2) {
      strcpy(error, "value is expected");
      return TSDB_CODE_INVALID_SQL;
    }

    if (getTimestampInUsFromStr(valueToken.z, valueToken.n, &interval) != TSDB_CODE_SUCCESS) {
      return TSDB_CODE_INVALID_SQL;
    }
    if (timePrec == TSDB_TIME_PRECISION_MILLI) {
      interval /= 1000;
    }

    if (sToken.type == TK_PLUS) {
      useconds += interval;
    } else {
      useconds = (useconds >= interval) ? useconds - interval : 0;
    }

    *next = pTokenEnd;
  }

  *time = useconds;
  return TSDB_CODE_SUCCESS;
}