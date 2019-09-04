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
struct TYPE_3__ {int /*<<< orphan*/ * priv_data; } ;
typedef  int /*<<< orphan*/  DVBSubtitleContext ;
typedef  int /*<<< orphan*/  AVSubtitle ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int encode_dvb_subtitles (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int dvbsub_encode(AVCodecContext *avctx,
                         unsigned char *buf, int buf_size,
                         const AVSubtitle *sub)
{
    DVBSubtitleContext *s = avctx->priv_data;
    int ret;

    ret = encode_dvb_subtitles(s, buf, sub);
    return ret;
}