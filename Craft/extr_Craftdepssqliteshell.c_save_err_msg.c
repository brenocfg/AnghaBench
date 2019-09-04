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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 char* sqlite3_malloc (int) ; 
 int strlen30 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *save_err_msg(
  sqlite3 *db            /* Database to query */
){
  int nErrMsg = 1+strlen30(sqlite3_errmsg(db));
  char *zErrMsg = sqlite3_malloc(nErrMsg);
  if( zErrMsg ){
    memcpy(zErrMsg, sqlite3_errmsg(db), nErrMsg);
  }
  return zErrMsg;
}