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
struct TYPE_3__ {int codec_id; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
#define  AV_CODEC_ID_CODEC2 131 
#define  AV_CODEC_ID_MP1 130 
#define  AV_CODEC_ID_MP2 129 
#define  AV_CODEC_ID_MP3 128 

__attribute__((used)) static int determinable_frame_size(AVCodecContext *avctx)
{
    switch(avctx->codec_id) {
    case AV_CODEC_ID_MP1:
    case AV_CODEC_ID_MP2:
    case AV_CODEC_ID_MP3:
    case AV_CODEC_ID_CODEC2:
        return 1;
    }

    return 0;
}