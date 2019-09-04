#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_8__ {int id; } ;
typedef  TYPE_1__ AVCodec ;

/* Variables and functions */
 scalar_t__ av_codec_is_decoder (TYPE_1__ const*) ; 
 scalar_t__ av_codec_is_encoder (TYPE_1__ const*) ; 
 TYPE_1__* av_codec_next (TYPE_1__ const*) ; 

__attribute__((used)) static const AVCodec *next_codec_for_id(enum AVCodecID id, const AVCodec *prev,
                                        int encoder)
{
    while ((prev = av_codec_next(prev))) {
        if (prev->id == id &&
            (encoder ? av_codec_is_encoder(prev) : av_codec_is_decoder(prev)))
            return prev;
    }
    return NULL;
}