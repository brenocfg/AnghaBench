#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  ref; } ;
struct TYPE_6__ {int /*<<< orphan*/  enc; TYPE_1__ cc; } ;
typedef  TYPE_2__ LibWebPAnimContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  WebPAnimEncoderDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int libwebp_anim_encode_close(AVCodecContext *avctx)
{
    LibWebPAnimContext *s = avctx->priv_data;
    av_frame_free(&s->cc.ref);
    WebPAnimEncoderDelete(s->enc);

    return 0;
}