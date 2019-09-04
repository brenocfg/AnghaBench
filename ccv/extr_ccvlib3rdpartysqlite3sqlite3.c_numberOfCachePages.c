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
typedef  int i64 ;
struct TYPE_3__ {scalar_t__ szCache; int szPage; int szExtra; } ;
typedef  TYPE_1__ PCache ;

/* Variables and functions */

__attribute__((used)) static int numberOfCachePages(PCache *p){
  if( p->szCache>=0 ){
    /* IMPLEMENTATION-OF: R-42059-47211 If the argument N is positive then the
    ** suggested cache size is set to N. */
    return p->szCache;
  }else{
    /* IMPLEMENTATION-OF: R-61436-13639 If the argument N is negative, then
    ** the number of cache pages is adjusted to use approximately abs(N*1024)
    ** bytes of memory. */
    return (int)((-1024*(i64)p->szCache)/(p->szPage+p->szExtra));
  }
}