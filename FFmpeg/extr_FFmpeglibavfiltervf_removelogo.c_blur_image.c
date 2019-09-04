#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int y1; int y2; int x1; int x2; } ;
typedef  TYPE_1__ FFBoundingBox ;

/* Variables and functions */
 int /*<<< orphan*/  av_image_copy_plane (scalar_t__*,int,scalar_t__ const*,int,int,int) ; 
 scalar_t__ blur_pixel (int***,scalar_t__ const*,int,scalar_t__*,int,int,int,int,int) ; 

__attribute__((used)) static void blur_image(int ***mask,
                       const uint8_t *src_data,  int src_linesize,
                             uint8_t *dst_data,  int dst_linesize,
                       const uint8_t *mask_data, int mask_linesize,
                       int w, int h, int direct,
                       FFBoundingBox *bbox)
{
    int x, y;
    uint8_t *dst_line;
    const uint8_t *src_line;

    if (!direct)
        av_image_copy_plane(dst_data, dst_linesize, src_data, src_linesize, w, h);

    for (y = bbox->y1; y <= bbox->y2; y++) {
        src_line = src_data + src_linesize * y;
        dst_line = dst_data + dst_linesize * y;

        for (x = bbox->x1; x <= bbox->x2; x++) {
             if (mask_data[y * mask_linesize + x]) {
                /* Only process if we are in the mask. */
                 dst_line[x] = blur_pixel(mask,
                                          mask_data, mask_linesize,
                                          dst_data, dst_linesize,
                                          w, h, x, y);
            } else {
                /* Else just copy the data. */
                if (!direct)
                    dst_line[x] = src_line[x];
            }
        }
    }
}