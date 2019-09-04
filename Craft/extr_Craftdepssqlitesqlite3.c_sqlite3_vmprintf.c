#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zBase ;
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_5__ {int useMalloc; } ;
typedef  TYPE_1__ StrAccum ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_MAX_LENGTH ; 
 int SQLITE_PRINT_BUF_SIZE ; 
 char* sqlite3StrAccumFinish (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3StrAccumInit (TYPE_1__*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VXPrintf (TYPE_1__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_initialize () ; 

char *sqlite3_vmprintf(const char *zFormat, va_list ap){
  char *z;
  char zBase[SQLITE_PRINT_BUF_SIZE];
  StrAccum acc;
#ifndef SQLITE_OMIT_AUTOINIT
  if( sqlite3_initialize() ) return 0;
#endif
  sqlite3StrAccumInit(&acc, zBase, sizeof(zBase), SQLITE_MAX_LENGTH);
  acc.useMalloc = 2;
  sqlite3VXPrintf(&acc, 0, zFormat, ap);
  z = sqlite3StrAccumFinish(&acc);
  return z;
}