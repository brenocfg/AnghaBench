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
typedef  char u8 ;
struct TYPE_5__ {int validYMD; int Y; int M; int D; scalar_t__ validTZ; scalar_t__ validJD; scalar_t__ validHMS; } ;
typedef  TYPE_1__ DateTime ;

/* Variables and functions */
 int /*<<< orphan*/  computeJD (TYPE_1__*) ; 
 int getDigits (char const*,int,int /*<<< orphan*/ ,int,char,int*,int,int,int,char,int*,int,int,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ parseHhMmSs (char const*,TYPE_1__*) ; 
 scalar_t__ sqlite3Isspace (char const) ; 

__attribute__((used)) static int parseYyyyMmDd(const char *zDate, DateTime *p){
  int Y, M, D, neg;

  if( zDate[0]=='-' ){
    zDate++;
    neg = 1;
  }else{
    neg = 0;
  }
  if( getDigits(zDate,4,0,9999,'-',&Y,2,1,12,'-',&M,2,1,31,0,&D)!=3 ){
    return 1;
  }
  zDate += 10;
  while( sqlite3Isspace(*zDate) || 'T'==*(u8*)zDate ){ zDate++; }
  if( parseHhMmSs(zDate, p)==0 ){
    /* We got the time */
  }else if( *zDate==0 ){
    p->validHMS = 0;
  }else{
    return 1;
  }
  p->validJD = 0;
  p->validYMD = 1;
  p->Y = neg ? -Y : Y;
  p->M = M;
  p->D = D;
  if( p->validTZ ){
    computeJD(p);
  }
  return 0;
}