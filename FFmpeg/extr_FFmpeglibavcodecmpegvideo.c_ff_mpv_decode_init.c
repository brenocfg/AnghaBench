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
struct TYPE_8__ {int /*<<< orphan*/  codec_tag; int /*<<< orphan*/  workaround_bugs; TYPE_1__* codec; int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; } ;
struct TYPE_7__ {int /*<<< orphan*/  codec_tag; int /*<<< orphan*/  workaround_bugs; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_3__* avctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  avpriv_toupper4 (int /*<<< orphan*/ ) ; 

void ff_mpv_decode_init(MpegEncContext *s, AVCodecContext *avctx)
{
    s->avctx           = avctx;
    s->width           = avctx->coded_width;
    s->height          = avctx->coded_height;
    s->codec_id        = avctx->codec->id;
    s->workaround_bugs = avctx->workaround_bugs;

    /* convert fourcc to upper case */
    s->codec_tag          = avpriv_toupper4(avctx->codec_tag);
}