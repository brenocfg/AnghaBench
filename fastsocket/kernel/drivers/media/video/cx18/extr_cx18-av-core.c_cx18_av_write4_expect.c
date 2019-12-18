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
typedef  scalar_t__ u16 ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx18_write_reg_expect (struct cx18*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cx18_av_write4_expect(struct cx18 *cx, u16 addr, u32 value, u32 eval, u32 mask)
{
	cx18_write_reg_expect(cx, value, 0xc40000 + addr, eval, mask);
	return 0;
}