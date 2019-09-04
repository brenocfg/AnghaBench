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
struct TYPE_3__ {int /*<<< orphan*/  sad; int /*<<< orphan*/  convolution_y; int /*<<< orphan*/  convolution_x; } ;
typedef  TYPE_1__ VMAFMotionDSPContext ;

/* Variables and functions */
 int /*<<< orphan*/  convolution_x ; 
 int /*<<< orphan*/  convolution_y_10bit ; 
 int /*<<< orphan*/  convolution_y_8bit ; 
 int /*<<< orphan*/  image_sad ; 

__attribute__((used)) static void vmafmotiondsp_init(VMAFMotionDSPContext *dsp, int bpp) {
    dsp->convolution_x = convolution_x;
    dsp->convolution_y = bpp == 10 ? convolution_y_10bit : convolution_y_8bit;
    dsp->sad = image_sad;
}