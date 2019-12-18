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
typedef  int /*<<< orphan*/  u32 ;
struct pm3_par {scalar_t__ v_regs; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  fb_writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void PM3_WRITE_REG(struct pm3_par *par, s32 off, u32 v)
{
	fb_writel(v, par->v_regs + off);
}