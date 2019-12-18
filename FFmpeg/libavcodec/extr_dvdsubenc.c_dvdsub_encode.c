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
typedef  int /*<<< orphan*/  AVSubtitle ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int encode_dvd_subtitles (int /*<<< orphan*/ *,unsigned char*,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int dvdsub_encode(AVCodecContext *avctx,
                         unsigned char *buf, int buf_size,
                         const AVSubtitle *sub)
{
    //DVDSubtitleContext *s = avctx->priv_data;
    int ret;

    ret = encode_dvd_subtitles(avctx, buf, buf_size, sub);
    return ret;
}