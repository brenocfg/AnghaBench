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
struct TYPE_9__ {unsigned int width; unsigned int height; } ;
typedef  TYPE_3__ zbar_image_t ;
struct TYPE_8__ {int xsub2; int ysub2; } ;
struct TYPE_7__ {TYPE_2__ yuv; } ;
struct TYPE_10__ {scalar_t__ group; TYPE_1__ p; } ;
typedef  TYPE_4__ zbar_format_def_t ;

/* Variables and functions */
 scalar_t__ ZBAR_FMT_GRAY ; 

__attribute__((used)) static inline void uv_roundup (zbar_image_t *img,
                               const zbar_format_def_t *fmt)
{
    unsigned xmask, ymask;
    if(fmt->group == ZBAR_FMT_GRAY)
        return;
    xmask = (1 << fmt->p.yuv.xsub2) - 1;
    if(img->width & xmask)
        img->width = (img->width + xmask) & ~xmask;
    ymask = (1 << fmt->p.yuv.ysub2) - 1;
    if(img->height & ymask)
        img->height = (img->height + ymask) & ~ymask;
}