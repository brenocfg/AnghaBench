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
 int /*<<< orphan*/  SQLITE_MISUSE_BKPT ; 
 char** sqlite3CompileOptions (int*) ; 
 scalar_t__ sqlite3IsIdChar (unsigned char) ; 
 scalar_t__ sqlite3StrNICmp (char const*,char const*,int) ; 
 int sqlite3Strlen30 (char const*) ; 

int sqlite3_compileoption_used(const char *zOptName){
  int i, n;
  int nOpt;
  const char **azCompileOpt;
 
#if SQLITE_ENABLE_API_ARMOR
  if( zOptName==0 ){
    (void)SQLITE_MISUSE_BKPT;
    return 0;
  }
#endif

  azCompileOpt = sqlite3CompileOptions(&nOpt);

  if( sqlite3StrNICmp(zOptName, "SQLITE_", 7)==0 ) zOptName += 7;
  n = sqlite3Strlen30(zOptName);

  /* Since nOpt is normally in single digits, a linear search is 
  ** adequate. No need for a binary search. */
  for(i=0; i<nOpt; i++){
    if( sqlite3StrNICmp(zOptName, azCompileOpt[i], n)==0
     && sqlite3IsIdChar((unsigned char)azCompileOpt[i][n])==0
    ){
      return 1;
    }
  }
  return 0;
}