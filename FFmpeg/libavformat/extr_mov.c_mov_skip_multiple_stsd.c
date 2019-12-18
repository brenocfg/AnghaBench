#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int video_codec_id; } ;
struct TYPE_4__ {TYPE_3__* fc; } ;
typedef  TYPE_1__ MOVContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int AV_RL32 (char*) ; 
 int MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ff_codec_get_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_codec_movvideo_tags ; 

__attribute__((used)) static int mov_skip_multiple_stsd(MOVContext *c, AVIOContext *pb,
                                  int codec_tag, int format,
                                  int64_t size)
{
    int video_codec_id = ff_codec_get_id(ff_codec_movvideo_tags, format);

    if (codec_tag &&
         (codec_tag != format &&
          // AVID 1:1 samples with differing data format and codec tag exist
          (codec_tag != AV_RL32("AV1x") || format != AV_RL32("AVup")) &&
          // prores is allowed to have differing data format and codec tag
          codec_tag != AV_RL32("apcn") && codec_tag != AV_RL32("apch") &&
          // so is dv (sigh)
          codec_tag != AV_RL32("dvpp") && codec_tag != AV_RL32("dvcp") &&
          (c->fc->video_codec_id ? video_codec_id != c->fc->video_codec_id
                                 : codec_tag != MKTAG('j','p','e','g')))) {
        /* Multiple fourcc, we skip JPEG. This is not correct, we should
         * export it as a separate AVStream but this needs a few changes
         * in the MOV demuxer, patch welcome. */

        av_log(c->fc, AV_LOG_WARNING, "multiple fourcc not supported\n");
        avio_skip(pb, size);
        return 1;
    }

    return 0;
}