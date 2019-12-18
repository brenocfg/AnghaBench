#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int width; } ;
struct TYPE_4__ {unsigned int width; } ;
struct TYPE_6__ {TYPE_2__ pix; TYPE_1__ pix_mp; } ;
struct v4l2_format {TYPE_3__ fmt; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ V4L2_TYPE_IS_MULTIPLANAR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int v4l2_get_width(struct v4l2_format *fmt)
{
    return V4L2_TYPE_IS_MULTIPLANAR(fmt->type) ? fmt->fmt.pix_mp.width : fmt->fmt.pix.width;
}