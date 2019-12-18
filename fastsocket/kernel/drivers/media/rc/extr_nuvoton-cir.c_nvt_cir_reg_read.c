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
typedef  scalar_t__ u8 ;
struct nvt_dev {scalar_t__ cir_addr; } ;

/* Variables and functions */
 scalar_t__ inb (scalar_t__) ; 

__attribute__((used)) static u8 nvt_cir_reg_read(struct nvt_dev *nvt, u8 offset)
{
	u8 val;

	val = inb(nvt->cir_addr + offset);

	return val;
}