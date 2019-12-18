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
struct cafe_camera {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cafe_reg_write_mask (struct cafe_camera*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void cafe_reg_clear_bit(struct cafe_camera *cam,
		unsigned int reg, unsigned int val)
{
	cafe_reg_write_mask(cam, reg, 0, val);
}