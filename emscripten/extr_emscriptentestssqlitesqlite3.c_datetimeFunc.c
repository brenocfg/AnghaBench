#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zBuf ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_4__ {scalar_t__ s; int /*<<< orphan*/  m; int /*<<< orphan*/  h; int /*<<< orphan*/  D; int /*<<< orphan*/  M; int /*<<< orphan*/  Y; } ;
typedef  TYPE_1__ DateTime ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  computeYMD_HMS (TYPE_1__*) ; 
 scalar_t__ isDate (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void datetimeFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  DateTime x;
  if( isDate(context, argc, argv, &x)==0 ){
    char zBuf[100];
    computeYMD_HMS(&x);
    sqlite3_snprintf(sizeof(zBuf), zBuf, "%04d-%02d-%02d %02d:%02d:%02d",
                     x.Y, x.M, x.D, x.h, x.m, (int)(x.s));
    sqlite3_result_text(context, zBuf, -1, SQLITE_TRANSIENT);
  }
}