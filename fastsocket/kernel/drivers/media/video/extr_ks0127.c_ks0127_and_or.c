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
typedef  size_t u8 ;
struct v4l2_subdev {int dummy; } ;
struct ks0127 {size_t* regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ks0127_write (struct v4l2_subdev*,size_t,size_t) ; 
 struct ks0127* to_ks0127 (struct v4l2_subdev*) ; 

__attribute__((used)) static void ks0127_and_or(struct v4l2_subdev *sd, u8 reg, u8 and_v, u8 or_v)
{
	struct ks0127 *ks = to_ks0127(sd);

	u8 val = ks->regs[reg];
	val = (val & and_v) | or_v;
	ks0127_write(sd, reg, val);
}