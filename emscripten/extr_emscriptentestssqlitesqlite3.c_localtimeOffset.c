#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct tm {int tm_year; int tm_mon; int tm_mday; int tm_sec; scalar_t__ tm_min; scalar_t__ tm_hour; } ;
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  sLocal ;
typedef  int i64 ;
struct TYPE_5__ {int Y; int M; int D; double s; int iJD; int validYMD; int validHMS; scalar_t__ validTZ; scalar_t__ validJD; scalar_t__ m; scalar_t__ h; scalar_t__ tz; } ;
typedef  TYPE_1__ DateTime ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  computeJD (TYPE_1__*) ; 
 int /*<<< orphan*/  computeYMD_HMS (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osLocaltime (scalar_t__*,struct tm*) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static sqlite3_int64 localtimeOffset(
  DateTime *p,                    /* Date at which to calculate offset */
  sqlite3_context *pCtx,          /* Write error here if one occurs */
  int *pRc                        /* OUT: Error code. SQLITE_OK or ERROR */
){
  DateTime x, y;
  time_t t;
  struct tm sLocal;

  /* Initialize the contents of sLocal to avoid a compiler warning. */
  memset(&sLocal, 0, sizeof(sLocal));

  x = *p;
  computeYMD_HMS(&x);
  if( x.Y<1971 || x.Y>=2038 ){
    x.Y = 2000;
    x.M = 1;
    x.D = 1;
    x.h = 0;
    x.m = 0;
    x.s = 0.0;
  } else {
    int s = (int)(x.s + 0.5);
    x.s = s;
  }
  x.tz = 0;
  x.validJD = 0;
  computeJD(&x);
  t = (time_t)(x.iJD/1000 - 21086676*(i64)10000);
  if( osLocaltime(&t, &sLocal) ){
    sqlite3_result_error(pCtx, "local time unavailable", -1);
    *pRc = SQLITE_ERROR;
    return 0;
  }
  y.Y = sLocal.tm_year + 1900;
  y.M = sLocal.tm_mon + 1;
  y.D = sLocal.tm_mday;
  y.h = sLocal.tm_hour;
  y.m = sLocal.tm_min;
  y.s = sLocal.tm_sec;
  y.validYMD = 1;
  y.validHMS = 1;
  y.validJD = 0;
  y.validTZ = 0;
  computeJD(&y);
  *pRc = SQLITE_OK;
  return y.iJD - x.iJD;
}