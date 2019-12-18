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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SPEC0_MakeStatus ; 
 int /*<<< orphan*/  SPEC1_MakeStatus ; 
 int /*<<< orphan*/  SPEC2_MakeStatus ; 
 scalar_t__ __pad_initialized ; 
 int /*<<< orphan*/  __pad_makestatus ; 
 int __pad_spec ; 

void PAD_SetSpec(u32 spec)
{
	if(__pad_initialized) return;

	__pad_spec = 0;
	if(spec==0) __pad_makestatus = SPEC0_MakeStatus;
	else if(spec==1) __pad_makestatus = SPEC1_MakeStatus;
	else if(spec<6) __pad_makestatus = SPEC2_MakeStatus;

	__pad_spec = spec;
}