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
typedef  int u8 ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int* nouveau_perf_table (struct drm_device*,int*) ; 

__attribute__((used)) static u8 *
nouveau_perf_entry(struct drm_device *dev, int idx,
		   u8 *ver, u8 *hdr, u8 *cnt, u8 *len)
{
	u8 *perf = nouveau_perf_table(dev, ver);
	if (perf) {
		if (*ver >= 0x12 && *ver < 0x20 && idx < perf[2]) {
			*hdr = perf[3];
			*cnt = 0;
			*len = 0;
			return perf + perf[0] + idx * perf[3];
		} else
		if (*ver >= 0x20 && *ver < 0x40 && idx < perf[2]) {
			*hdr = perf[3];
			*cnt = perf[4];
			*len = perf[5];
			return perf + perf[1] + idx * (*hdr + (*cnt * *len));
		} else
		if (*ver >= 0x40 && *ver < 0x41 && idx < perf[5]) {
			*hdr = perf[2];
			*cnt = perf[4];
			*len = perf[3];
			return perf + perf[1] + idx * (*hdr + (*cnt * *len));
		}
	}
	return NULL;
}