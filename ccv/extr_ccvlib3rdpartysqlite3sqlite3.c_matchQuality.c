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
typedef  int u8 ;
struct TYPE_3__ {scalar_t__ xSFunc; int nArg; int funcFlags; } ;
typedef  TYPE_1__ FuncDef ;

/* Variables and functions */
 int FUNC_PERFECT_MATCH ; 
 int SQLITE_FUNC_ENCMASK ; 

__attribute__((used)) static int matchQuality(
  FuncDef *p,     /* The function we are evaluating for match quality */
  int nArg,       /* Desired number of arguments.  (-1)==any */
  u8 enc          /* Desired text encoding */
){
  int match;

  /* nArg of -2 is a special case */
  if( nArg==(-2) ) return (p->xSFunc==0) ? 0 : FUNC_PERFECT_MATCH;

  /* Wrong number of arguments means "no match" */
  if( p->nArg!=nArg && p->nArg>=0 ) return 0;

  /* Give a better score to a function with a specific number of arguments
  ** than to function that accepts any number of arguments. */
  if( p->nArg==nArg ){
    match = 4;
  }else{
    match = 1;
  }

  /* Bonus points if the text encoding matches */
  if( enc==(p->funcFlags & SQLITE_FUNC_ENCMASK) ){
    match += 2;  /* Exact encoding match */
  }else if( (enc & p->funcFlags & 2)!=0 ){
    match += 1;  /* Both are UTF16, but with different byte orders */
  }

  return match;
}