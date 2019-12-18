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
typedef  int /*<<< orphan*/  uint8_t ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_PTV_TV_DATA ; 
 int /*<<< orphan*/  NV_PTV_TV_INDEX ; 
 int /*<<< orphan*/  nv_read_ptv (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_write_ptv (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t nv_read_tv_enc(struct drm_device *dev, uint8_t reg)
{
	nv_write_ptv(dev, NV_PTV_TV_INDEX, reg);
	return nv_read_ptv(dev, NV_PTV_TV_DATA);
}