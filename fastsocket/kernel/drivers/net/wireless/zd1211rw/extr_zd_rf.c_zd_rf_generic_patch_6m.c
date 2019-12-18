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
struct zd_rf {int dummy; } ;

/* Variables and functions */
 int zd_chip_generic_patch_6m_band (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zd_rf_to_chip (struct zd_rf*) ; 

int zd_rf_generic_patch_6m(struct zd_rf *rf, u8 channel)
{
	return zd_chip_generic_patch_6m_band(zd_rf_to_chip(rf), channel);
}