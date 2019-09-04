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
struct TYPE_4__ {int rate; int bits; int block_align; } ;
typedef  TYPE_1__ SIFFContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ TAG_SHDR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 void* avio_rl16 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_rl32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int create_audio_stream (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int siff_parse_soun(AVFormatContext *s, SIFFContext *c, AVIOContext *pb)
{
    if (avio_rl32(pb) != TAG_SHDR) {
        av_log(s, AV_LOG_ERROR, "Header chunk is missing\n");
        return AVERROR_INVALIDDATA;
    }
    if (avio_rb32(pb) != 8) {
        av_log(s, AV_LOG_ERROR, "Header chunk size is incorrect\n");
        return AVERROR_INVALIDDATA;
    }
    avio_skip(pb, 4); // unknown value
    c->rate        = avio_rl16(pb);
    c->bits        = avio_rl16(pb);
    c->block_align = c->rate * (c->bits >> 3);
    return create_audio_stream(s, c);
}