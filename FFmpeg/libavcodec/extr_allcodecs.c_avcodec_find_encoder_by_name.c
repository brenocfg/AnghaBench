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
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  av_codec_is_encoder ; 
 int /*<<< orphan*/ * find_codec_by_name (char const*,int /*<<< orphan*/ ) ; 

AVCodec *avcodec_find_encoder_by_name(const char *name)
{
    return find_codec_by_name(name, av_codec_is_encoder);
}