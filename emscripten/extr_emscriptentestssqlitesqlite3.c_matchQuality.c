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
typedef  scalar_t__ u8 ;
struct TYPE_3__ {int nArg; scalar_t__ xFunc; scalar_t__ xStep; scalar_t__ iPrefEnc; } ;
typedef  TYPE_1__ FuncDef ;

/* Variables and functions */
 scalar_t__ SQLITE_UTF16BE ; 
 scalar_t__ SQLITE_UTF16LE ; 

__attribute__((used)) static int matchQuality(FuncDef *p, int nArg, u8 enc){
  int match = 0;
  if( p->nArg==-1 || p->nArg==nArg 
   || (nArg==-1 && (p->xFunc!=0 || p->xStep!=0))
  ){
    match = 1;
    if( p->nArg==nArg || nArg==-1 ){
      match = 4;
    }
    if( enc==p->iPrefEnc ){
      match += 2;
    }
    else if( (enc==SQLITE_UTF16LE && p->iPrefEnc==SQLITE_UTF16BE) ||
             (enc==SQLITE_UTF16BE && p->iPrefEnc==SQLITE_UTF16LE) ){
      match += 1;
    }
  }
  return match;
}