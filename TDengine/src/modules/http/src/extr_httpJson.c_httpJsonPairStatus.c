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
typedef  int /*<<< orphan*/  JsonBuf ;

/* Variables and functions */
 int TSDB_CODE_DB_NOT_SELECTED ; 
 int TSDB_CODE_INVALID_TABLE ; 
 int /*<<< orphan*/  httpJsonItemToken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  httpJsonPair (int /*<<< orphan*/ *,char*,int,char*,int) ; 
 int /*<<< orphan*/  httpJsonPairIntVal (int /*<<< orphan*/ *,char*,int,int) ; 
 scalar_t__ strlen (char*) ; 
 char** tsError ; 

void httpJsonPairStatus(JsonBuf* buf, int code) {
  if (code == 0) {
    httpJsonPair(buf, "status", 6, "succ", 4);
  } else {
    httpJsonPair(buf, "status", 6, "error", 5);
    httpJsonItemToken(buf);
    httpJsonPairIntVal(buf, "code", 4, code);
    if (code >= 0) {
      httpJsonItemToken(buf);
      if (code == TSDB_CODE_DB_NOT_SELECTED) {
        httpJsonPair(buf, "desc", 4, "failed to create database", 23);
      } else if (code == TSDB_CODE_INVALID_TABLE) {
        httpJsonPair(buf, "desc", 4, "failed to create table", 22);
      } else
        httpJsonPair(buf, "desc", 4, tsError[code], (int)strlen(tsError[code]));
    }
  }
}