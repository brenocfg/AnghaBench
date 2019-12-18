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
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int read_div (struct drm_device*,int /*<<< orphan*/ ,int,int) ; 
 int read_pll (struct drm_device*,int) ; 

__attribute__((used)) static u32
read_mem(struct drm_device *dev)
{
	struct nouveau_device *device = nouveau_dev(dev);
	u32 ssel = nv_rd32(device, 0x1373f0);
	if (ssel & 0x00000001)
		return read_div(dev, 0, 0x137300, 0x137310);
	return read_pll(dev, 0x132000);
}