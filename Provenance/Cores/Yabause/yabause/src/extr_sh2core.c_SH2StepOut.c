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
struct TYPE_4__ {void (* callBack ) (void*,u32,void*) ;int enabled; scalar_t__ address; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {TYPE_1__ stepOverOut; } ;
typedef  TYPE_2__ SH2_struct ;

/* Variables and functions */
 scalar_t__ SH2Core ; 
 int /*<<< orphan*/  SH2ST_STEPOUT ; 

void SH2StepOut(SH2_struct *context, void (*func)(void *, u32, void *))
{
   if (SH2Core)
   {
      context->stepOverOut.callBack = func;
      context->stepOverOut.type = SH2ST_STEPOUT;
      context->stepOverOut.enabled = 1;
      context->stepOverOut.address = 0;
   }
}