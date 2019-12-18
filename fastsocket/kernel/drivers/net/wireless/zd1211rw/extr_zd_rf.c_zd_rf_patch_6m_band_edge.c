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
struct zd_rf {int (* patch_6m_band_edge ) (struct zd_rf*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct zd_rf*,int /*<<< orphan*/ ) ; 

int zd_rf_patch_6m_band_edge(struct zd_rf *rf, u8 channel)
{
	if (!rf->patch_6m_band_edge)
		return 0;

	return rf->patch_6m_band_edge(rf, channel);
}