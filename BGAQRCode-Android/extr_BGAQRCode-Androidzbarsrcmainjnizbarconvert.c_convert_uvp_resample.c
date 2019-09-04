#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned long width; unsigned long height; unsigned long datalen; scalar_t__ data; } ;
typedef  TYPE_1__ zbar_image_t ;
typedef  int /*<<< orphan*/  zbar_format_def_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  convert_y_resize (TYPE_1__*,int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/  const*,unsigned long) ; 
 scalar_t__ malloc (unsigned long) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,unsigned long) ; 
 int /*<<< orphan*/  uv_roundup (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int uvp_size (TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void convert_uvp_resample (zbar_image_t *dst,
                                  const zbar_format_def_t *dstfmt,
                                  const zbar_image_t *src,
                                  const zbar_format_def_t *srcfmt)
{
    unsigned long dstn, dstm2;
    uv_roundup(dst, dstfmt);
    dstn = dst->width * dst->height;
    dstm2 = uvp_size(dst, dstfmt) * 2;
    dst->datalen = dstn + dstm2;
    dst->data = malloc(dst->datalen);
    if(!dst->data) return;
    convert_y_resize(dst, dstfmt, src, srcfmt, dstn);
    if(dstm2)
        memset((uint8_t*)dst->data + dstn, 0x80, dstm2);
}