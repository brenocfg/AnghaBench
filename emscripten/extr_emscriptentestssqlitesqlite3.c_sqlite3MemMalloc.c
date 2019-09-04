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
 int* malloc (int) ; 
 TYPE_1__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void *sqlite3MemMalloc(int nByte){
  sqlite3_int64 *p;
  assert( nByte>0 );
  nByte = ROUND8(nByte);
  p = malloc( nByte+8 );
  if( p ){
    p[0] = nByte;
    p++;
  }else{
    testcase( sqlite3GlobalConfig.xLog!=0 );
    sqlite3_log(SQLITE_NOMEM, "failed to allocate %u bytes of memory", nByte);
  }
  return (void *)p;
}