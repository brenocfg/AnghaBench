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
struct drm_display_mode {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct drm_display_mode* drm_gtf_mode_complex (struct drm_device*,int,int,int,int,int,int,int,int,int) ; 

struct drm_display_mode *
drm_gtf_mode(struct drm_device *dev, int hdisplay, int vdisplay, int vrefresh,
	     bool lace, int margins)
{
	return drm_gtf_mode_complex(dev, hdisplay, vdisplay, vrefresh, lace,
				    margins, 600, 40 * 2, 128, 20 * 2);
}