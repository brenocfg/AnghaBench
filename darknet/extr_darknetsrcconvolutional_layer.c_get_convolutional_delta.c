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
typedef  int /*<<< orphan*/  image ;
struct TYPE_3__ {int /*<<< orphan*/  delta; int /*<<< orphan*/  out_c; int /*<<< orphan*/  out_h; int /*<<< orphan*/  out_w; } ;
typedef  TYPE_1__ convolutional_layer ;

/* Variables and functions */
 int /*<<< orphan*/  float_to_image (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

image get_convolutional_delta(convolutional_layer l)
{
    return float_to_image(l.out_w,l.out_h,l.out_c,l.delta);
}