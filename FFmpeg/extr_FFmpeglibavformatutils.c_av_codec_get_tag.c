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
 int /*<<< orphan*/  av_codec_get_tag2 (int /*<<< orphan*/  const* const*,int,unsigned int*) ; 

unsigned int av_codec_get_tag(const AVCodecTag *const *tags, enum AVCodecID id)
{
    unsigned int tag;
    if (!av_codec_get_tag2(tags, id, &tag))
        return 0;
    return tag;
}