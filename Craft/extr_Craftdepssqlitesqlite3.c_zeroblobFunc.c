#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_3__ {scalar_t__* aLimit; } ;
typedef  TYPE_1__ sqlite3 ;
typedef  scalar_t__ i64 ;

/* Variables and functions */
 size_t SQLITE_LIMIT_LENGTH ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_error_toobig (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_zeroblob (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void zeroblobFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  i64 n;
  sqlite3 *db = sqlite3_context_db_handle(context);
  assert( argc==1 );
  UNUSED_PARAMETER(argc);
  n = sqlite3_value_int64(argv[0]);
  testcase( n==db->aLimit[SQLITE_LIMIT_LENGTH] );
  testcase( n==db->aLimit[SQLITE_LIMIT_LENGTH]+1 );
  if( n>db->aLimit[SQLITE_LIMIT_LENGTH] ){
    sqlite3_result_error_toobig(context);
  }else{
    sqlite3_result_zeroblob(context, (int)n); /* IMP: R-00293-64994 */
  }
}