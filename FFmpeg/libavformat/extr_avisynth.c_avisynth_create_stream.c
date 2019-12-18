#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* priv_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
struct TYPE_11__ {int /*<<< orphan*/  vi; } ;
typedef  TYPE_1__ AviSynthContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_UNKNOWN ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avisynth_create_stream_audio (TYPE_3__*,TYPE_2__*) ; 
 int avisynth_create_stream_video (TYPE_3__*,TYPE_2__*) ; 
 scalar_t__ avs_has_audio (int /*<<< orphan*/ ) ; 
 scalar_t__ avs_has_video (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int avisynth_create_stream(AVFormatContext *s)
{
    AviSynthContext *avs = s->priv_data;
    AVStream *st;
    int ret;
    int id = 0;

    if (avs_has_video(avs->vi)) {
        st = avformat_new_stream(s, NULL);
        if (!st)
            return AVERROR_UNKNOWN;
        st->id = id++;
        if (ret = avisynth_create_stream_video(s, st))
            return ret;
    }
    if (avs_has_audio(avs->vi)) {
        st = avformat_new_stream(s, NULL);
        if (!st)
            return AVERROR_UNKNOWN;
        st->id = id++;
        if (ret = avisynth_create_stream_audio(s, st))
            return ret;
    }
    return 0;
}