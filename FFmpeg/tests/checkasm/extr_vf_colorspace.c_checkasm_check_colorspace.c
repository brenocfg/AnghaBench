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

/* Variables and functions */
 int /*<<< orphan*/  check_multiply3x3 () ; 
 int /*<<< orphan*/  check_rgb2yuv () ; 
 int /*<<< orphan*/  check_yuv2rgb () ; 
 int /*<<< orphan*/  check_yuv2yuv () ; 

void checkasm_check_colorspace(void)
{
    check_yuv2yuv();
    check_yuv2rgb();
    check_rgb2yuv();
    check_multiply3x3();
}