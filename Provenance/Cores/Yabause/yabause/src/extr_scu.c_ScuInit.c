#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  scudspregs_struct ;
struct TYPE_5__ {scalar_t__ inbreakpoint; int /*<<< orphan*/ * BreakpointCallBack; scalar_t__ numcodebreakpoints; TYPE_1__* codebreakpoint; } ;
typedef  TYPE_2__ scubp_struct ;
struct TYPE_4__ {int addr; } ;
typedef  int /*<<< orphan*/  Scu ;

/* Variables and functions */
 int MAX_BREAKPOINTS ; 
 TYPE_2__* ScuBP ; 
 int /*<<< orphan*/ * ScuDsp ; 
 int /*<<< orphan*/ * ScuRegs ; 
 scalar_t__ calloc (int,int) ; 

int ScuInit(void) {
   int i;

   if ((ScuRegs = (Scu *) calloc(1, sizeof(Scu))) == NULL)
      return -1;

   if ((ScuDsp = (scudspregs_struct *) calloc(1, sizeof(scudspregs_struct))) == NULL)
      return -1;

   if ((ScuBP = (scubp_struct *) calloc(1, sizeof(scubp_struct))) == NULL)
      return -1;

   for (i = 0; i < MAX_BREAKPOINTS; i++)
      ScuBP->codebreakpoint[i].addr = 0xFFFFFFFF;
   ScuBP->numcodebreakpoints = 0;
   ScuBP->BreakpointCallBack=NULL;
   ScuBP->inbreakpoint=0;
   
   return 0;
}