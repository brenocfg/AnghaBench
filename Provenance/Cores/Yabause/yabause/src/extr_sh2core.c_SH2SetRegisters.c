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
typedef  int /*<<< orphan*/  sh2regs_struct ;
struct TYPE_2__ {int /*<<< orphan*/  (* SetRegisters ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  SH2_struct ;

/* Variables and functions */
 TYPE_1__* SH2Core ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void SH2SetRegisters(SH2_struct *context, sh2regs_struct * r)
{
   if (r != NULL) {
      SH2Core->SetRegisters(context, r);
   }
}