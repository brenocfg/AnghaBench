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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int i64 ;

/* Variables and functions */
#define  SQLITE_INTEGER 129 
#define  SQLITE_NULL 128 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_null (int /*<<< orphan*/ *) ; 
 double sqlite3_value_double (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void absFunc(sqlite3_context *context, int argc, sqlite3_value **argv){
  assert( argc==1 );
  UNUSED_PARAMETER(argc);
  switch( sqlite3_value_type(argv[0]) ){
    case SQLITE_INTEGER: {
      i64 iVal = sqlite3_value_int64(argv[0]);
      if( iVal<0 ){
        if( (iVal<<1)==0 ){
          /* IMP: R-35460-15084 If X is the integer -9223372036854775807 then
          ** abs(X) throws an integer overflow error since there is no
          ** equivalent positive 64-bit two complement value. */
          sqlite3_result_error(context, "integer overflow", -1);
          return;
        }
        iVal = -iVal;
      } 
      sqlite3_result_int64(context, iVal);
      break;
    }
    case SQLITE_NULL: {
      /* IMP: R-37434-19929 Abs(X) returns NULL if X is NULL. */
      sqlite3_result_null(context);
      break;
    }
    default: {
      /* Because sqlite3_value_double() returns 0.0 if the argument is not
      ** something that can be converted into a number, we have:
      ** IMP: R-57326-31541 Abs(X) return 0.0 if X is a string or blob that
      ** cannot be converted to a numeric value. 
      */
      double rVal = sqlite3_value_double(argv[0]);
      if( rVal<0 ) rVal = -rVal;
      sqlite3_result_double(context, rVal);
      break;
    }
  }
}