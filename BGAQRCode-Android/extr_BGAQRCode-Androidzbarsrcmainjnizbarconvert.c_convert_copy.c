#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int width; int height; struct TYPE_7__* next; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  datalen; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ zbar_image_t ;
typedef  int /*<<< orphan*/  zbar_format_def_t ;

/* Variables and functions */
 int /*<<< orphan*/  _zbar_image_refcnt (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cleanup_ref ; 
 int /*<<< orphan*/  convert_y_resize (TYPE_1__*,int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void convert_copy (zbar_image_t *dst,
                          const zbar_format_def_t *dstfmt,
                          const zbar_image_t *src,
                          const zbar_format_def_t *srcfmt)
{
    if(src->width == dst->width &&
       src->height == dst->height) {
        zbar_image_t *s = (zbar_image_t*)src;
        dst->data = src->data;
        dst->datalen = src->datalen;
        dst->cleanup = cleanup_ref;
        dst->next = s;
        _zbar_image_refcnt(s, 1);
    }
    else
        /* NB only for GRAY/YUV_PLANAR formats */
        convert_y_resize(dst, dstfmt, src, srcfmt, dst->width * dst->height);
}