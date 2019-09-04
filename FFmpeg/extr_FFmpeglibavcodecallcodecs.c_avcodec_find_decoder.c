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
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  av_codec_is_decoder ; 
 int /*<<< orphan*/ * find_codec (int,int /*<<< orphan*/ ) ; 

AVCodec *avcodec_find_decoder(enum AVCodecID id)
{
    return find_codec(id, av_codec_is_decoder);
}