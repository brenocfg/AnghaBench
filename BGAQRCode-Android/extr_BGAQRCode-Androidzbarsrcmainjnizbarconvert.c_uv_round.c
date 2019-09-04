#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int width; int height; } ;
typedef  TYPE_3__ zbar_image_t ;
struct TYPE_8__ {int xsub2; int ysub2; } ;
struct TYPE_7__ {TYPE_2__ yuv; } ;
struct TYPE_10__ {TYPE_1__ p; } ;
typedef  TYPE_4__ zbar_format_def_t ;

/* Variables and functions */

__attribute__((used)) static inline void uv_round (zbar_image_t *img,
                             const zbar_format_def_t *fmt)
{
    img->width >>= fmt->p.yuv.xsub2;
    img->width <<= fmt->p.yuv.xsub2;
    img->height >>= fmt->p.yuv.ysub2;
    img->height <<= fmt->p.yuv.ysub2;
}