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
struct zd_chip {int /*<<< orphan*/  rf; int /*<<< orphan*/  patch_6m_band_edge; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int zd_rf_patch_6m_band_edge (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patch_6m_band_edge(struct zd_chip *chip, u8 channel)
{
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	if (!chip->patch_6m_band_edge)
		return 0;

	return zd_rf_patch_6m_band_edge(&chip->rf, channel);
}