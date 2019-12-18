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
typedef  int /*<<< orphan*/  u32 ;
struct compareInfo {int /*<<< orphan*/  matchSet; } ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_3__ {int* aLimit; } ;
typedef  TYPE_1__ sqlite3 ;

/* Variables and functions */
 scalar_t__ SQLITE_BLOB ; 
 size_t SQLITE_LIMIT_LIKE_PATTERN_LENGTH ; 
 scalar_t__ SQLITE_MATCH ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ patternCompare (unsigned char const*,unsigned char const*,struct compareInfo*,int /*<<< orphan*/ ) ; 
 int sqlite3Utf8CharLen (char*,int) ; 
 int /*<<< orphan*/  sqlite3Utf8Read (unsigned char const**) ; 
 TYPE_1__* sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_like_count ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 struct compareInfo* sqlite3_user_data (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 unsigned char const* sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void likeFunc(
  sqlite3_context *context, 
  int argc, 
  sqlite3_value **argv
){
  const unsigned char *zA, *zB;
  u32 escape;
  int nPat;
  sqlite3 *db = sqlite3_context_db_handle(context);
  struct compareInfo *pInfo = sqlite3_user_data(context);

#ifdef SQLITE_LIKE_DOESNT_MATCH_BLOBS
  if( sqlite3_value_type(argv[0])==SQLITE_BLOB
   || sqlite3_value_type(argv[1])==SQLITE_BLOB
  ){
#ifdef SQLITE_TEST
    sqlite3_like_count++;
#endif
    sqlite3_result_int(context, 0);
    return;
  }
#endif
  zB = sqlite3_value_text(argv[0]);
  zA = sqlite3_value_text(argv[1]);

  /* Limit the length of the LIKE or GLOB pattern to avoid problems
  ** of deep recursion and N*N behavior in patternCompare().
  */
  nPat = sqlite3_value_bytes(argv[0]);
  testcase( nPat==db->aLimit[SQLITE_LIMIT_LIKE_PATTERN_LENGTH] );
  testcase( nPat==db->aLimit[SQLITE_LIMIT_LIKE_PATTERN_LENGTH]+1 );
  if( nPat > db->aLimit[SQLITE_LIMIT_LIKE_PATTERN_LENGTH] ){
    sqlite3_result_error(context, "LIKE or GLOB pattern too complex", -1);
    return;
  }
  assert( zB==sqlite3_value_text(argv[0]) );  /* Encoding did not change */

  if( argc==3 ){
    /* The escape character string must consist of a single UTF-8 character.
    ** Otherwise, return an error.
    */
    const unsigned char *zEsc = sqlite3_value_text(argv[2]);
    if( zEsc==0 ) return;
    if( sqlite3Utf8CharLen((char*)zEsc, -1)!=1 ){
      sqlite3_result_error(context, 
          "ESCAPE expression must be a single character", -1);
      return;
    }
    escape = sqlite3Utf8Read(&zEsc);
  }else{
    escape = pInfo->matchSet;
  }
  if( zA && zB ){
#ifdef SQLITE_TEST
    sqlite3_like_count++;
#endif
    sqlite3_result_int(context,
                      patternCompare(zB, zA, pInfo, escape)==SQLITE_MATCH);
  }
}