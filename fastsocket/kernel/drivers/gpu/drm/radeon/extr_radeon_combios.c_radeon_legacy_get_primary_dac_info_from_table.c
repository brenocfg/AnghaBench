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
struct radeon_encoder_primary_dac {int /*<<< orphan*/  ps2_pdac_adj; } ;
struct radeon_device {size_t family; } ;

/* Variables and functions */
 int /*<<< orphan*/ * default_primarydac_adj ; 

__attribute__((used)) static void radeon_legacy_get_primary_dac_info_from_table(struct radeon_device *rdev,
							  struct radeon_encoder_primary_dac *p_dac)
{
	p_dac->ps2_pdac_adj = default_primarydac_adj[rdev->family];
	return;
}