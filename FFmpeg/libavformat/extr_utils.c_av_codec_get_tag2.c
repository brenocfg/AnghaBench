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
struct TYPE_3__ {scalar_t__ id; unsigned int tag; } ;
typedef  TYPE_1__ AVCodecTag ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_NONE ; 

int av_codec_get_tag2(const AVCodecTag * const *tags, enum AVCodecID id,
                      unsigned int *tag)
{
    int i;
    for (i = 0; tags && tags[i]; i++) {
        const AVCodecTag *codec_tags = tags[i];
        while (codec_tags->id != AV_CODEC_ID_NONE) {
            if (codec_tags->id == id) {
                *tag = codec_tags->tag;
                return 1;
            }
            codec_tags++;
        }
    }
    return 0;
}