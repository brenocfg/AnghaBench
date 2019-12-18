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
typedef  int /*<<< orphan*/  u8 ;
struct isp1301 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP1301_INTERRUPT_LATCH ; 
 int /*<<< orphan*/  isp1301_clear_bits (struct isp1301*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp1301_get_u8 (struct isp1301*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 isp1301_clear_latch(struct isp1301 *isp)
{
	u8 latch = isp1301_get_u8(isp, ISP1301_INTERRUPT_LATCH);
	isp1301_clear_bits(isp, ISP1301_INTERRUPT_LATCH, latch);
	return latch;
}