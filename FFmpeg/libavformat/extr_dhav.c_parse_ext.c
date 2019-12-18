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
struct TYPE_6__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int width; int height; int video_codec; int frame_rate; int audio_channels; int audio_codec; int sample_rate; } ;
typedef  TYPE_1__ DHAVContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int FF_ARRAY_ELEMS (void**) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int avio_r8 (int /*<<< orphan*/ ) ; 
 void* avio_rl16 (int /*<<< orphan*/ ) ; 
 int avio_skip (int /*<<< orphan*/ ,int) ; 
 void** sample_rates ; 

__attribute__((used)) static int parse_ext(AVFormatContext *s, int length)
{
    DHAVContext *dhav = s->priv_data;
    int index, ret = 0;

    while (length > 0) {
        int type = avio_r8(s->pb);

        switch (type) {
        case 0x80:
            ret = avio_skip(s->pb, 1);
            dhav->width  = 8 * avio_r8(s->pb);
            dhav->height = 8 * avio_r8(s->pb);
            length -= 4;
            break;
        case 0x81:
            ret = avio_skip(s->pb, 1);
            dhav->video_codec = avio_r8(s->pb);
            dhav->frame_rate = avio_r8(s->pb);
            length -= 4;
            break;
        case 0x82:
            ret = avio_skip(s->pb, 3);
            dhav->width  = avio_rl16(s->pb);
            dhav->height = avio_rl16(s->pb);
            length -= 8;
            break;
        case 0x83:
            dhav->audio_channels = avio_r8(s->pb);
            dhav->audio_codec = avio_r8(s->pb);
            index = avio_r8(s->pb);
            if (index < FF_ARRAY_ELEMS(sample_rates)) {
                dhav->sample_rate = sample_rates[index];
            } else {
                dhav->sample_rate = 8000;
            }
            length -= 4;
            break;
        case 0x88:
            ret = avio_skip(s->pb, 7);
            length -= 8;
            break;
        case 0x8c:
            ret = avio_skip(s->pb, 1);
            dhav->audio_channels = avio_r8(s->pb);
            dhav->audio_codec = avio_r8(s->pb);
            index = avio_r8(s->pb);
            if (index < FF_ARRAY_ELEMS(sample_rates)) {
                dhav->sample_rate = sample_rates[index];
            } else {
                dhav->sample_rate = 8000;
            }
            ret = avio_skip(s->pb, 3);
            length -= 8;
            break;
        case 0x91:
        case 0x92:
        case 0x93:
        case 0x95:
        case 0x9a:
        case 0x9b: // sample aspect ratio
        case 0xb3:
            ret = avio_skip(s->pb, 7);
            length -= 8;
            break;
        case 0x84:
        case 0x85:
        case 0x8b:
        case 0x94:
        case 0x96:
        case 0xa0:
        case 0xb2:
        case 0xb4:
            ret = avio_skip(s->pb, 3);
            length -= 4;
            break;
        default:
            av_log(s, AV_LOG_INFO, "Unknown type: %X, skipping rest of header.\n", type);
            ret = avio_skip(s->pb, length - 1);
            length = 0;
        }

        if (ret < 0)
            return ret;
    }

    return 0;
}