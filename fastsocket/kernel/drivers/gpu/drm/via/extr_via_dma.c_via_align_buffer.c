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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  drm_via_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  HC_DUMMY ; 
 int /*<<< orphan*/  VIA_OUT_RING_QW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t *via_align_buffer(drm_via_private_t *dev_priv,
					 uint32_t * vb, int qw_count)
{
	for (; qw_count > 0; --qw_count)
		VIA_OUT_RING_QW(HC_DUMMY, HC_DUMMY);
	return vb;
}