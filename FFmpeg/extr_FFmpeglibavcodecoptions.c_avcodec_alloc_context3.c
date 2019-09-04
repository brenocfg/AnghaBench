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
typedef  int /*<<< orphan*/  AVCodecContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_malloc (int) ; 
 scalar_t__ init_context_defaults (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

AVCodecContext *avcodec_alloc_context3(const AVCodec *codec)
{
    AVCodecContext *avctx= av_malloc(sizeof(AVCodecContext));

    if (!avctx)
        return NULL;

    if (init_context_defaults(avctx, codec) < 0) {
        av_free(avctx);
        return NULL;
    }

    return avctx;
}