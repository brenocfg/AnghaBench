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
struct put_image_params {int src_scan_h; int dst_h; int src_scan_w; int dst_w; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int check_overlay_scaling(struct put_image_params *rec)
{
	u32 tmp;

	/* downscaling limit is 8.0 */
	tmp = ((rec->src_scan_h << 16) / rec->dst_h) >> 16;
	if (tmp > 7)
		return -EINVAL;
	tmp = ((rec->src_scan_w << 16) / rec->dst_w) >> 16;
	if (tmp > 7)
		return -EINVAL;

	return 0;
}