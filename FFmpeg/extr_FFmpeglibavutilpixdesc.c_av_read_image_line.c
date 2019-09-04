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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  AVPixFmtDescriptor ;

/* Variables and functions */
 int /*<<< orphan*/  av_read_image_line2 (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int const*,int /*<<< orphan*/  const*,int,int,int,int,int,int) ; 

void av_read_image_line(uint16_t *dst,
                        const uint8_t *data[4], const int linesize[4],
                        const AVPixFmtDescriptor *desc,
                        int x, int y, int c, int w,
                        int read_pal_component)
{
    av_read_image_line2(dst, data, linesize, desc,x, y, c, w,
                        read_pal_component,
                        2);
}