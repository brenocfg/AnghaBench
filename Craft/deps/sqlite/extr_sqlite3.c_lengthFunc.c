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

/* Variables and functions */
#define  SQLITE_BLOB 131 
#define  SQLITE_FLOAT 130 
#define  SQLITE_INTEGER 129 
 int /*<<< orphan*/  SQLITE_SKIP_UTF8 (unsigned char const*) ; 
#define  SQLITE_TEXT 128 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_null (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 unsigned char* sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lengthFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  int len;

  assert( argc==1 );
  UNUSED_PARAMETER(argc);
  switch( sqlite3_value_type(argv[0]) ){
    case SQLITE_BLOB:
    case SQLITE_INTEGER:
    case SQLITE_FLOAT: {
      sqlite3_result_int(context, sqlite3_value_bytes(argv[0]));
      break;
    }
    case SQLITE_TEXT: {
      const unsigned char *z = sqlite3_value_text(argv[0]);
      if( z==0 ) return;
      len = 0;
      while( *z ){
        len++;
        SQLITE_SKIP_UTF8(z);
      }
      sqlite3_result_int(context, len);
      break;
    }
    default: {
      sqlite3_result_null(context);
      break;
    }
  }
}