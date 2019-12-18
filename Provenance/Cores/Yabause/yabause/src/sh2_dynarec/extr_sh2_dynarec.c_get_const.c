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
typedef  int /*<<< orphan*/  u64 ;
struct regstat {char* regmap; int /*<<< orphan*/ * cpmap; } ;

/* Variables and functions */
 int HOST_REGS ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  printf (char*,char) ; 

u64 get_const(struct regstat *cur,signed char reg)
{
  int hr;
  if(reg<0) return 0;
  for (hr=0;hr<HOST_REGS;hr++) {
    if(cur->regmap[hr]==reg) {
      return cur->cpmap[hr];
    }
  }
  printf("Unknown constant in r%d\n",reg);
  exit(1);
}