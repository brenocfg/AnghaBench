#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_4__ {scalar_t__ nb_components; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;

/* Variables and functions */
 int FF_LOSS_ALPHA ; 
 scalar_t__ av_get_padded_bits_per_pixel (TYPE_1__ const*) ; 
 int av_get_pix_fmt_loss (int,int,int) ; 
 TYPE_1__* av_pix_fmt_desc_get (int) ; 
 int get_pix_fmt_score (int,int,int*,int) ; 

enum AVPixelFormat av_find_best_pix_fmt_of_2(enum AVPixelFormat dst_pix_fmt1, enum AVPixelFormat dst_pix_fmt2,
                                             enum AVPixelFormat src_pix_fmt, int has_alpha, int *loss_ptr)
{
    enum AVPixelFormat dst_pix_fmt;
    int loss1, loss2, loss_mask;
    const AVPixFmtDescriptor *desc1 = av_pix_fmt_desc_get(dst_pix_fmt1);
    const AVPixFmtDescriptor *desc2 = av_pix_fmt_desc_get(dst_pix_fmt2);
    int score1, score2;

    if (!desc1) {
        dst_pix_fmt = dst_pix_fmt2;
    } else if (!desc2) {
        dst_pix_fmt = dst_pix_fmt1;
    } else {
        loss_mask= loss_ptr?~*loss_ptr:~0; /* use loss mask if provided */
        if(!has_alpha)
            loss_mask &= ~FF_LOSS_ALPHA;

        score1 = get_pix_fmt_score(dst_pix_fmt1, src_pix_fmt, &loss1, loss_mask);
        score2 = get_pix_fmt_score(dst_pix_fmt2, src_pix_fmt, &loss2, loss_mask);

        if (score1 == score2) {
            if(av_get_padded_bits_per_pixel(desc2) != av_get_padded_bits_per_pixel(desc1)) {
                dst_pix_fmt = av_get_padded_bits_per_pixel(desc2) < av_get_padded_bits_per_pixel(desc1) ? dst_pix_fmt2 : dst_pix_fmt1;
            } else {
                dst_pix_fmt = desc2->nb_components < desc1->nb_components ? dst_pix_fmt2 : dst_pix_fmt1;
            }
        } else {
            dst_pix_fmt = score1 < score2 ? dst_pix_fmt2 : dst_pix_fmt1;
        }
    }

    if (loss_ptr)
        *loss_ptr = av_get_pix_fmt_loss(dst_pix_fmt, src_pix_fmt, has_alpha);
    return dst_pix_fmt;
}