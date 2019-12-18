#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* frames; } ;
typedef  TYPE_2__ VP9SharedContext ;
typedef  int /*<<< orphan*/  VAAPIDecodePicture ;
struct TYPE_8__ {TYPE_2__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/ * hwaccel_picture_private; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 size_t CUR_FRAME ; 
 int ff_vaapi_decode_issue (TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vaapi_vp9_end_frame(AVCodecContext *avctx)
{
    const VP9SharedContext *h = avctx->priv_data;
    VAAPIDecodePicture *pic = h->frames[CUR_FRAME].hwaccel_picture_private;

    return ff_vaapi_decode_issue(avctx, pic);
}