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
struct TYPE_8__ {int datalen; unsigned long width; unsigned long height; scalar_t__ data; } ;
typedef  TYPE_1__ zbar_image_t ;
typedef  int /*<<< orphan*/  zbar_format_def_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  convert_y_resize (TYPE_1__*,int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/  const*,unsigned long) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  uv_roundup (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int uvp_size (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  zprintf (int,char*,int,int,unsigned long,int,int,int,int) ; 

__attribute__((used)) static void convert_uvp_append (zbar_image_t *dst,
                                const zbar_format_def_t *dstfmt,
                                const zbar_image_t *src,
                                const zbar_format_def_t *srcfmt)
{
    unsigned long n;
    uv_roundup(dst, dstfmt);
    dst->datalen = uvp_size(dst, dstfmt) * 2;
    n = dst->width * dst->height;
    dst->datalen += n;
    assert(src->datalen >= src->width * src->height);
    zprintf(24, "dst=%dx%d (%lx) %lx src=%dx%d %lx\n",
            dst->width, dst->height, n, dst->datalen,
            src->width, src->height, src->datalen);
    dst->data = malloc(dst->datalen);
    if(!dst->data) return;
    convert_y_resize(dst, dstfmt, src, srcfmt, n);
    memset((uint8_t*)dst->data + n, 0x80, dst->datalen - n);
}