#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  crop_h; int /*<<< orphan*/  crop_w; int /*<<< orphan*/  crop_y; int /*<<< orphan*/  crop_x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ zbar_image_t ;

/* Variables and functions */

__attribute__((used)) static inline void _zbar_image_copy_size (zbar_image_t *dst,
                                          const zbar_image_t *src)
{
    dst->width = src->width;
    dst->height = src->height;
    dst->crop_x = src->crop_x;
    dst->crop_y = src->crop_y;
    dst->crop_w = src->crop_w;
    dst->crop_h = src->crop_h;
}