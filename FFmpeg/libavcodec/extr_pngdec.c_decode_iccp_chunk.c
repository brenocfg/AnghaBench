#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_13__ {scalar_t__ buffer; } ;
struct TYPE_12__ {int /*<<< orphan*/  len; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; int /*<<< orphan*/  metadata; } ;
struct TYPE_10__ {TYPE_6__ gb; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ PNGDecContext ;
typedef  TYPE_2__ AVFrameSideData ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_3__ AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_FRAME_DATA_ICC_PROFILE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int av_bprint_finalize (TYPE_3__*,char**) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* av_frame_new_side_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (scalar_t__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bytestream2_get_byte (TYPE_6__*) ; 
 int /*<<< orphan*/  bytestream2_skip (TYPE_6__*,int) ; 
 int decode_zbuf (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_iccp_chunk(PNGDecContext *s, int length, AVFrame *f)
{
    int ret, cnt = 0;
    uint8_t *data, profile_name[82];
    AVBPrint bp;
    AVFrameSideData *sd;

    while ((profile_name[cnt++] = bytestream2_get_byte(&s->gb)) && cnt < 81);
    if (cnt > 80) {
        av_log(s->avctx, AV_LOG_ERROR, "iCCP with invalid name!\n");
        return AVERROR_INVALIDDATA;
    }

    length = FFMAX(length - cnt, 0);

    if (bytestream2_get_byte(&s->gb) != 0) {
        av_log(s->avctx, AV_LOG_ERROR, "iCCP with invalid compression!\n");
        return AVERROR_INVALIDDATA;
    }

    length = FFMAX(length - 1, 0);

    if ((ret = decode_zbuf(&bp, s->gb.buffer, s->gb.buffer + length)) < 0)
        return ret;

    ret = av_bprint_finalize(&bp, (char **)&data);
    if (ret < 0)
        return ret;

    sd = av_frame_new_side_data(f, AV_FRAME_DATA_ICC_PROFILE, bp.len);
    if (!sd) {
        av_free(data);
        return AVERROR(ENOMEM);
    }

    av_dict_set(&sd->metadata, "name", profile_name, 0);
    memcpy(sd->data, data, bp.len);
    av_free(data);

    /* ICC compressed data and CRC */
    bytestream2_skip(&s->gb, length + 4);

    return 0;
}