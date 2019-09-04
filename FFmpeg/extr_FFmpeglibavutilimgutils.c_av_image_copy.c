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
typedef  int ptrdiff_t ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int /*<<< orphan*/  image_copy (int /*<<< orphan*/ **,int*,int /*<<< orphan*/  const**,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  image_copy_plane ; 

void av_image_copy(uint8_t *dst_data[4], int dst_linesizes[4],
                   const uint8_t *src_data[4], const int src_linesizes[4],
                   enum AVPixelFormat pix_fmt, int width, int height)
{
    ptrdiff_t dst_linesizes1[4], src_linesizes1[4];
    int i;

    for (i = 0; i < 4; i++) {
        dst_linesizes1[i] = dst_linesizes[i];
        src_linesizes1[i] = src_linesizes[i];
    }

    image_copy(dst_data, dst_linesizes1, src_data, src_linesizes1, pix_fmt,
               width, height, image_copy_plane);
}