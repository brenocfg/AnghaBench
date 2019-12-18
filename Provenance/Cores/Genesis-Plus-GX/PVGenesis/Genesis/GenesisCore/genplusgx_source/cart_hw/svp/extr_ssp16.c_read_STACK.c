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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * stack; } ;

/* Variables and functions */
 int EL_ANOMALY ; 
 int EL_SVP ; 
 int /*<<< orphan*/  GET_PPC_OFFS () ; 
 int /*<<< orphan*/  elprintf (int,char*,size_t,int /*<<< orphan*/ ) ; 
 size_t rSTACK ; 
 TYPE_1__* ssp ; 

__attribute__((used)) static u32 read_STACK(void)
{
  --rSTACK;
  if ((short)rSTACK < 0) {
    rSTACK = 5;
#ifdef LOG_SVP
    elprintf(EL_ANOMALY|EL_SVP, "ssp FIXME: stack underflow! (%i) @ %04x", rSTACK, GET_PPC_OFFS());
#endif
  }
  return ssp->stack[rSTACK];
}