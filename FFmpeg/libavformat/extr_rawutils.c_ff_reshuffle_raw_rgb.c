#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_11__ {int bits_per_coded_sample; int width; int height; } ;
struct TYPE_10__ {int size; scalar_t__ data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_2__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMIN (int,int) ; 
 int av_new_packet (TYPE_1__*,int) ; 
 TYPE_1__* av_packet_alloc () ; 
 int av_packet_copy_props (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  av_packet_free (TYPE_1__**) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

int ff_reshuffle_raw_rgb(AVFormatContext *s, AVPacket **ppkt, AVCodecParameters *par, int expected_stride)
{
    int ret;
    AVPacket *pkt = *ppkt;
    int64_t bpc = par->bits_per_coded_sample != 15 ? par->bits_per_coded_sample : 16;
    int min_stride = (par->width * bpc + 7) >> 3;
    int with_pal_size = min_stride * par->height + 1024;
    int contains_pal = bpc == 8 && pkt->size == with_pal_size;
    int size = contains_pal ? min_stride * par->height : pkt->size;
    int stride = size / par->height;
    int padding = expected_stride - FFMIN(expected_stride, stride);
    int y;
    AVPacket *new_pkt;

    if (pkt->size == expected_stride * par->height)
        return 0;
    if (size != stride * par->height)
        return 0;

    new_pkt = av_packet_alloc();
    if (!new_pkt)
        return AVERROR(ENOMEM);

    ret = av_new_packet(new_pkt, expected_stride * par->height);
    if (ret < 0)
        goto fail;

    ret = av_packet_copy_props(new_pkt, pkt);
    if (ret < 0)
        goto fail;

    for (y = 0; y<par->height; y++) {
        memcpy(new_pkt->data + y*expected_stride, pkt->data + y*stride, FFMIN(expected_stride, stride));
        memset(new_pkt->data + y*expected_stride + expected_stride - padding, 0, padding);
    }

    *ppkt = new_pkt;
    return 1 + contains_pal;
fail:
    av_packet_free(&new_pkt);

    return ret;
}