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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  subimage_with_fill_template (int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ *,unsigned int,unsigned int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void subimage_with_fill(uint16_t *src, unsigned x, unsigned y,
        unsigned stride, unsigned width, unsigned height, uint16_t *dst,
        unsigned dst_width, unsigned dst_height, int is_interlaced, int is_top_field)
{
    subimage_with_fill_template(src, x, y, stride, width, height, dst, dst_width, dst_height, 0, is_interlaced, is_top_field);
}