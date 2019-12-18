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
typedef  int /*<<< orphan*/  Parse ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3ErrorMsg (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ sqlite3StrNICmp (char const*,char*,int) ; 
 int sqlite3Strlen30 (char const*) ; 

__attribute__((used)) static int isSystemTable(Parse *pParse, const char *zName){
  if( sqlite3Strlen30(zName)>6 && 0==sqlite3StrNICmp(zName, "sqlite_", 7) ){
    sqlite3ErrorMsg(pParse, "table %s may not be altered", zName);
    return 1;
  }
  return 0;
}