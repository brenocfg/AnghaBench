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
typedef  size_t u16 ;
struct sn9c102_device {int* reg; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 

int sn9c102_pread_reg(struct sn9c102_device* cam, u16 index)
{
	if (index >= ARRAY_SIZE(cam->reg))
		return -1;

	return cam->reg[index];
}