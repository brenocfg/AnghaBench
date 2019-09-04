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
typedef  int /*<<< orphan*/  MediaCodecDecContext ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_mediacodec_dec_unref (int /*<<< orphan*/ *) ; 

int ff_mediacodec_dec_close(AVCodecContext *avctx, MediaCodecDecContext *s)
{
    ff_mediacodec_dec_unref(s);

    return 0;
}