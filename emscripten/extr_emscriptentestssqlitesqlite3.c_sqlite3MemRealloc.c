#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_int64 ;
struct TYPE_2__ {scalar_t__ xLog; } ;

/* Variables and functions */
 int ROUND8 (int) ; 
 int /*<<< orphan*/  SQLITE_NOMEM ; 
 int /*<<< orphan*/  assert (int) ; 
 int* realloc (int*,int) ; 
 TYPE_1__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  sqlite3MemSize (void*) ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void *sqlite3MemRealloc(void *pPrior, int nByte){
  sqlite3_int64 *p = (sqlite3_int64*)pPrior;
  assert( pPrior!=0 && nByte>0 );
  assert( nByte==ROUND8(nByte) ); /* EV: R-46199-30249 */
  p--;
  p = realloc(p, nByte+8 );
  if( p ){
    p[0] = nByte;
    p++;
  }else{
    testcase( sqlite3GlobalConfig.xLog!=0 );
    sqlite3_log(SQLITE_NOMEM,
      "failed memory resize %u to %u bytes",
      sqlite3MemSize(pPrior), nByte);
  }
  return (void*)p;
}