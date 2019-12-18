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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MREG_END ; 
 scalar_t__ MREG_START ; 
 scalar_t__ __fsi_reg_read (scalar_t__) ; 
 TYPE_1__* master ; 

__attribute__((used)) static u32 fsi_master_read(u32 reg)
{
	if ((reg < MREG_START) ||
	    (reg > MREG_END))
		return 0;

	return __fsi_reg_read((u32)(master->base + reg));
}