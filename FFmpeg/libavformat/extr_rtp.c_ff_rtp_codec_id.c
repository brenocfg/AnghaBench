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
struct TYPE_2__ {scalar_t__ pt; int codec_type; int codec_id; int /*<<< orphan*/  enc_name; } ;

/* Variables and functions */
 int AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  av_strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* rtp_payload_types ; 

enum AVCodecID ff_rtp_codec_id(const char *buf, enum AVMediaType codec_type)
{
    int i;

    for (i = 0; rtp_payload_types[i].pt >= 0; i++)
        if (!av_strcasecmp(buf, rtp_payload_types[i].enc_name) && (codec_type == rtp_payload_types[i].codec_type))
            return rtp_payload_types[i].codec_id;

    return AV_CODEC_ID_NONE;
}