#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_8__ {TYPE_1__* codecpar; } ;
struct TYPE_7__ {void* height; void* width; scalar_t__ codec_tag; int /*<<< orphan*/  format; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_RAWVIDEO ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_r8 (int /*<<< orphan*/ *) ; 
 void* avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_find_pix_fmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frm_pix_fmt_tags ; 

__attribute__((used)) static int frm_read_header(AVFormatContext *avctx)
{
    AVIOContext *pb = avctx->pb;
    AVStream *st = avformat_new_stream(avctx, 0);
    if (!st)
        return AVERROR(ENOMEM);

    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id   = AV_CODEC_ID_RAWVIDEO;
    avio_skip(pb, 3);

    st->codecpar->format    = avpriv_find_pix_fmt(frm_pix_fmt_tags, avio_r8(pb));
    if (!st->codecpar->format)
        return AVERROR_INVALIDDATA;

    st->codecpar->codec_tag  = 0;
    st->codecpar->width      = avio_rl16(pb);
    st->codecpar->height     = avio_rl16(pb);
    return 0;
}