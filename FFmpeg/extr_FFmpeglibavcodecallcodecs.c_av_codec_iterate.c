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
 int /*<<< orphan*/  av_codec_init_static ; 
 int /*<<< orphan*/  av_codec_static_init ; 
 int /*<<< orphan*/ ** codec_list ; 
 int /*<<< orphan*/  ff_thread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const AVCodec *av_codec_iterate(void **opaque)
{
    uintptr_t i = (uintptr_t)*opaque;
    const AVCodec *c = codec_list[i];

    ff_thread_once(&av_codec_static_init, av_codec_init_static);

    if (c)
        *opaque = (void*)(i + 1);

    return c;
}