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
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  DateTime ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 scalar_t__ parseHhMmSs (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ parseYyyyMmDd (char const*,int /*<<< orphan*/ *) ; 
 int setDateTimeToCurrent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setRawDateNumber (int /*<<< orphan*/ *,double) ; 
 scalar_t__ sqlite3AtoF (char const*,double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3NotPureFunc (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3StrICmp (char const*,char*) ; 
 int /*<<< orphan*/  sqlite3Strlen30 (char const*) ; 

__attribute__((used)) static int parseDateOrTime(
  sqlite3_context *context, 
  const char *zDate, 
  DateTime *p
){
  double r;
  if( parseYyyyMmDd(zDate,p)==0 ){
    return 0;
  }else if( parseHhMmSs(zDate, p)==0 ){
    return 0;
  }else if( sqlite3StrICmp(zDate,"now")==0 && sqlite3NotPureFunc(context) ){
    return setDateTimeToCurrent(context, p);
  }else if( sqlite3AtoF(zDate, &r, sqlite3Strlen30(zDate), SQLITE_UTF8) ){
    setRawDateNumber(p, r);
    return 0;
  }
  return 1;
}