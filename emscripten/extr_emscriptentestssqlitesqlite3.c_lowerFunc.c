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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  scalar_t__ i64 ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__* contextMalloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char const*,int) ; 
 scalar_t__ sqlite3Tolower (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lowerFunc(sqlite3_context *context, int argc, sqlite3_value **argv){
  u8 *z1;
  const char *z2;
  int i, n;
  UNUSED_PARAMETER(argc);
  z2 = (char*)sqlite3_value_text(argv[0]);
  n = sqlite3_value_bytes(argv[0]);
  /* Verify that the call to _bytes() does not invalidate the _text() pointer */
  assert( z2==(char*)sqlite3_value_text(argv[0]) );
  if( z2 ){
    z1 = contextMalloc(context, ((i64)n)+1);
    if( z1 ){
      memcpy(z1, z2, n+1);
      for(i=0; z1[i]; i++){
        z1[i] = sqlite3Tolower(z1[i]);
      }
      sqlite3_result_text(context, (char *)z1, -1, sqlite3_free);
    }
  }
}