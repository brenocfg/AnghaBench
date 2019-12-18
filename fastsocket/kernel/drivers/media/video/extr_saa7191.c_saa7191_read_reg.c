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
typedef  size_t u8 ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {size_t* reg; } ;

/* Variables and functions */
 TYPE_1__* to_saa7191 (struct v4l2_subdev*) ; 

__attribute__((used)) static u8 saa7191_read_reg(struct v4l2_subdev *sd, u8 reg)
{
	return to_saa7191(sd)->reg[reg];
}