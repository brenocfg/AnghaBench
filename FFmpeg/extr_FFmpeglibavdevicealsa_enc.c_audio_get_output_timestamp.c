#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ snd_pcm_sframes_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {scalar_t__ timestamp; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ AlsaData ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ av_gettime () ; 
 int /*<<< orphan*/  snd_pcm_delay (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void
audio_get_output_timestamp(AVFormatContext *s1, int stream,
    int64_t *dts, int64_t *wall)
{
    AlsaData *s  = s1->priv_data;
    snd_pcm_sframes_t delay = 0;
    *wall = av_gettime();
    snd_pcm_delay(s->h, &delay);
    *dts = s->timestamp - delay;
}