#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pb; int /*<<< orphan*/  ctx_flags; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int width; int height; int /*<<< orphan*/ * st_audio; int /*<<< orphan*/  st_video; scalar_t__ remaining_audio_size; scalar_t__ remaining_frame_size; int /*<<< orphan*/  nb_frames; void* fps; void* bits_per_sample; } ;
typedef  TYPE_1__ AvsFormat ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVFMTCTX_NOHEADER ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int,int) ; 
 void* avio_rl16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int avs_read_header(AVFormatContext * s)
{
    AvsFormat *avs = s->priv_data;

    s->ctx_flags |= AVFMTCTX_NOHEADER;

    avio_skip(s->pb, 4);
    avs->width = avio_rl16(s->pb);
    avs->height = avio_rl16(s->pb);
    avs->bits_per_sample = avio_rl16(s->pb);
    avs->fps = avio_rl16(s->pb);
    avs->nb_frames = avio_rl32(s->pb);
    avs->remaining_frame_size = 0;
    avs->remaining_audio_size = 0;

    avs->st_video = avs->st_audio = NULL;

    if (avs->width != 318 || avs->height != 198)
        av_log(s, AV_LOG_ERROR, "This avs pretend to be %dx%d "
               "when the avs format is supposed to be 318x198 only.\n",
               avs->width, avs->height);

    return 0;
}