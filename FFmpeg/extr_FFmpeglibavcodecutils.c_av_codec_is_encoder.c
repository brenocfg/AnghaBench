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
struct TYPE_3__ {scalar_t__ send_frame; scalar_t__ encode2; scalar_t__ encode_sub; } ;
typedef  TYPE_1__ AVCodec ;

/* Variables and functions */

int av_codec_is_encoder(const AVCodec *codec)
{
    return codec && (codec->encode_sub || codec->encode2 ||codec->send_frame);
}