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
struct sh_fpu_hard_struct {int dummy; } ;
struct TYPE_2__ {struct sh_fpu_hard_struct hard; } ;

/* Variables and functions */
 TYPE_1__ init_fpuregs ; 

void fpinit(struct sh_fpu_hard_struct *fpregs)
{
	*fpregs = init_fpuregs.hard;
}