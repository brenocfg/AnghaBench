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
typedef  int /*<<< orphan*/  u16 ;
struct radeon_connector {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_dp_aux_native_write (struct radeon_connector*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_write_dpcd_reg(struct radeon_connector *radeon_connector,
				 u16 reg, u8 val)
{
	radeon_dp_aux_native_write(radeon_connector, reg, &val, 1, 0);
}