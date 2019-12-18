#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int last_good_pos; int type; int /*<<< orphan*/  timestamp; void* date; void* frame_number; void* frame_subnumber; void* channel; void* subtype; } ;
typedef  TYPE_1__ DHAVContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 void* MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 
 void* avio_r8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_rl16 (int /*<<< orphan*/ ) ; 
 void* avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int avio_skip (int /*<<< orphan*/ ,int) ; 
 int avio_tell (int /*<<< orphan*/ ) ; 
 int parse_ext (TYPE_2__*,int) ; 

__attribute__((used)) static int read_chunk(AVFormatContext *s)
{
    DHAVContext *dhav = s->priv_data;
    int frame_length, ext_length;
    int64_t start, end;
    int ret;

    if (avio_feof(s->pb))
        return AVERROR_EOF;

    if (avio_rl32(s->pb) != MKTAG('D','H','A','V')) {
        dhav->last_good_pos += 0x8000;
        avio_seek(s->pb, dhav->last_good_pos, SEEK_SET);

        while (avio_rl32(s->pb) != MKTAG('D','H','A','V')) {
            if (avio_feof(s->pb))
                return AVERROR_EOF;
            dhav->last_good_pos += 0x8000;
            ret = avio_skip(s->pb, 0x8000 - 4);
            if (ret < 0)
                return ret;
        }
    }

    start = avio_tell(s->pb) - 4;
    dhav->last_good_pos = start;
    dhav->type = avio_r8(s->pb);
    dhav->subtype = avio_r8(s->pb);
    dhav->channel = avio_r8(s->pb);
    dhav->frame_subnumber = avio_r8(s->pb);
    dhav->frame_number = avio_rl32(s->pb);
    frame_length = avio_rl32(s->pb);

    if (frame_length < 24)
        return AVERROR_INVALIDDATA;
    if (dhav->type == 0xf1) {
        ret = avio_skip(s->pb, frame_length - 16);
        return ret < 0 ? ret : 0;
    }

    dhav->date = avio_rl32(s->pb);
    dhav->timestamp = avio_rl16(s->pb);
    ext_length = avio_r8(s->pb);
    avio_skip(s->pb, 1); // checksum

    ret = parse_ext(s, ext_length);
    if (ret < 0)
        return ret;

    end = avio_tell(s->pb);

    return frame_length - 8 - (end - start);
}