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
typedef  int u32 ;
struct drm_radeon_private {int cs_id_scnt; int cs_id_wcnt; } ;

/* Variables and functions */

__attribute__((used)) static u32 radeon_cs_id_get(struct drm_radeon_private *radeon)
{
	/* FIXME: check if wrap affect last reported wrap & sequence */
	radeon->cs_id_scnt = (radeon->cs_id_scnt + 1) & 0x00FFFFFF;
	if (!radeon->cs_id_scnt) {
		/* increment wrap counter */
		radeon->cs_id_wcnt += 0x01000000;
		/* valid sequence counter start at 1 */
		radeon->cs_id_scnt = 1;
	}
	return (radeon->cs_id_scnt | radeon->cs_id_wcnt);
}