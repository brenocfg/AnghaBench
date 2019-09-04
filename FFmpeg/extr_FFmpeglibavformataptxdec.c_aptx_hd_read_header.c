#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* codecpar; } ;
struct TYPE_4__ {int bits_per_coded_sample; int /*<<< orphan*/  frame_size; int /*<<< orphan*/  block_align; int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  APTX_HD_BLOCK_SIZE ; 
 int /*<<< orphan*/  APTX_HD_PACKET_SIZE ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_CODEC_ID_APTX_HD ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* aptx_read_header_common (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aptx_hd_read_header(AVFormatContext *s)
{
    AVStream *st = aptx_read_header_common(s);
    if (!st)
        return AVERROR(ENOMEM);
    st->codecpar->codec_id = AV_CODEC_ID_APTX_HD;
    st->codecpar->bits_per_coded_sample = 6;
    st->codecpar->block_align = APTX_HD_BLOCK_SIZE;
    st->codecpar->frame_size = APTX_HD_PACKET_SIZE;
    return 0;
}