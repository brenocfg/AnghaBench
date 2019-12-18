#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_8__ {scalar_t__ (* GetPC ) (TYPE_1__*) ;} ;
struct TYPE_7__ {scalar_t__ cycles; } ;
typedef  TYPE_1__ SH2_struct ;

/* Variables and functions */
 TYPE_6__* SH2Core ; 
 int /*<<< orphan*/  SH2Exec (TYPE_1__*,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_1__*) ; 
 scalar_t__ stub2 (TYPE_1__*) ; 

void SH2Step(SH2_struct *context)
{
   if (SH2Core)
   {
      u32 tmp = SH2Core->GetPC(context);

      // Execute 1 instruction
      SH2Exec(context, context->cycles+1);

      // Sometimes it doesn't always execute one instruction,
      // let's make sure it did
      if (tmp == SH2Core->GetPC(context))
         SH2Exec(context, context->cycles+1);
   }
}