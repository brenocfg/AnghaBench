#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zNum ;
struct TYPE_2__ {unsigned int szTest; } ;

/* Variables and functions */
 TYPE_1__ g ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int,unsigned int,char*) ; 
 int /*<<< orphan*/  speedtest1_numbername (unsigned int,char*,int) ; 
 unsigned int swizzle (unsigned int,unsigned int) ; 

void testset_debug1(void){
  unsigned i, n;
  unsigned x1, x2;
  char zNum[2000];              /* A number name */

  n = g.szTest;
  for(i=1; i<=n; i++){
    x1 = swizzle(i, n);
    x2 = swizzle(x1, n);
    speedtest1_numbername(x1, zNum, sizeof(zNum));
    printf("%5d %5d %5d %s\n", i, x1, x2, zNum);
  }
}