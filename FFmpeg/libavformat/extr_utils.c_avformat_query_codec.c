#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_3__ {int (* query_codec ) (int,int) ;int video_codec; int audio_codec; int subtitle_codec; int data_codec; scalar_t__ codec_tag; } ;
typedef  TYPE_1__ AVOutputFormat ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  av_codec_get_tag2 (scalar_t__,int,unsigned int*) ; 
 int stub1 (int,int) ; 

int avformat_query_codec(const AVOutputFormat *ofmt, enum AVCodecID codec_id,
                         int std_compliance)
{
    if (ofmt) {
        unsigned int codec_tag;
        if (ofmt->query_codec)
            return ofmt->query_codec(codec_id, std_compliance);
        else if (ofmt->codec_tag)
            return !!av_codec_get_tag2(ofmt->codec_tag, codec_id, &codec_tag);
        else if (codec_id == ofmt->video_codec ||
                 codec_id == ofmt->audio_codec ||
                 codec_id == ofmt->subtitle_codec ||
                 codec_id == ofmt->data_codec)
            return 1;
    }
    return AVERROR_PATCHWELCOME;
}