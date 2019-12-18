#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
typedef  int /*<<< orphan*/  AVCodecTag ;

/* Variables and functions */
 int AV_CODEC_ID_NONE ; 
 int ff_codec_get_id (int /*<<< orphan*/  const* const,unsigned int) ; 

enum AVCodecID av_codec_get_id(const AVCodecTag *const *tags, unsigned int tag)
{
    int i;
    for (i = 0; tags && tags[i]; i++) {
        enum AVCodecID id = ff_codec_get_id(tags[i], tag);
        if (id != AV_CODEC_ID_NONE)
            return id;
    }
    return AV_CODEC_ID_NONE;
}