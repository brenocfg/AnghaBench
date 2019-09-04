#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_2__ {scalar_t__ id; } ;

/* Variables and functions */
 int AVMEDIA_TYPE_AUDIO ; 
 int AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 int FF_COMPLIANCE_NORMAL ; 
 int avcodec_get_type (int) ; 
 TYPE_1__* ff_mkv_codec_tags ; 

__attribute__((used)) static int mkv_query_codec(enum AVCodecID codec_id, int std_compliance)
{
    int i;
    for (i = 0; ff_mkv_codec_tags[i].id != AV_CODEC_ID_NONE; i++)
        if (ff_mkv_codec_tags[i].id == codec_id)
            return 1;

    if (std_compliance < FF_COMPLIANCE_NORMAL) {
        enum AVMediaType type = avcodec_get_type(codec_id);
        // mkv theoretically supports any video/audio through VFW/ACM
        if (type == AVMEDIA_TYPE_VIDEO || type == AVMEDIA_TYPE_AUDIO)
            return 1;
    }

    return 0;
}