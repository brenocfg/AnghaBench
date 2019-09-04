#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ uint8_t ;
typedef  int uint16_t ;
struct TYPE_10__ {int nb_components; int log2_chroma_w; int log2_chroma_h; int flags; int step; int depth; int /*<<< orphan*/  shift; int /*<<< orphan*/  offset; int /*<<< orphan*/  plane; struct TYPE_10__* comp; scalar_t__* name; } ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_2__ AVComponentDescriptor ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_BAYER ; 
 int AV_PIX_FMT_FLAG_BITSTREAM ; 
 int FF_ARRAY_ELEMS (TYPE_2__*) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int av_get_pix_fmt (scalar_t__*) ; 
 TYPE_2__* av_pix_fmt_descriptors ; 
 int /*<<< orphan*/  av_read_image_line (int*,void*,int*,TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_write_image_line (int*,TYPE_1__**,int*,TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void ff_check_pixfmt_descriptors(void){
    int i, j;

    for (i=0; i<FF_ARRAY_ELEMS(av_pix_fmt_descriptors); i++) {
        const AVPixFmtDescriptor *d = &av_pix_fmt_descriptors[i];
        uint8_t fill[4][8+6+3] = {{0}};
        uint8_t *data[4] = {fill[0], fill[1], fill[2], fill[3]};
        int linesize[4] = {0,0,0,0};
        uint16_t tmp[2];

        if (!d->name && !d->nb_components && !d->log2_chroma_w && !d->log2_chroma_h && !d->flags)
            continue;
//         av_log(NULL, AV_LOG_DEBUG, "Checking: %s\n", d->name);
        av_assert0(d->log2_chroma_w <= 3);
        av_assert0(d->log2_chroma_h <= 3);
        av_assert0(d->nb_components <= 4);
        av_assert0(d->name && d->name[0]);
        av_assert2(av_get_pix_fmt(d->name) == i);

        for (j=0; j<FF_ARRAY_ELEMS(d->comp); j++) {
            const AVComponentDescriptor *c = &d->comp[j];
            if(j>=d->nb_components) {
                av_assert0(!c->plane && !c->step && !c->offset && !c->shift && !c->depth);
                continue;
            }
            if (d->flags & AV_PIX_FMT_FLAG_BITSTREAM) {
                av_assert0(c->step >= c->depth);
            } else {
                av_assert0(8*c->step >= c->depth);
            }
            if (d->flags & AV_PIX_FMT_FLAG_BAYER)
                continue;
            av_read_image_line(tmp, (void*)data, linesize, d, 0, 0, j, 2, 0);
            av_assert0(tmp[0] == 0 && tmp[1] == 0);
            tmp[0] = tmp[1] = (1<<c->depth) - 1;
            av_write_image_line(tmp, data, linesize, d, 0, 0, j, 2);
        }
    }
}