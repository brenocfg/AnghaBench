#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  url; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_9__ {TYPE_1__* codecpar; } ;
struct TYPE_8__ {int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_7__ {int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; } ;
typedef  TYPE_2__ OSSAudioData ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int ff_oss_audio_open (TYPE_4__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int audio_write_header(AVFormatContext *s1)
{
    OSSAudioData *s = s1->priv_data;
    AVStream *st;
    int ret;

    st = s1->streams[0];
    s->sample_rate = st->codecpar->sample_rate;
    s->channels = st->codecpar->channels;
    ret = ff_oss_audio_open(s1, 1, s1->url);
    if (ret < 0) {
        return AVERROR(EIO);
    } else {
        return 0;
    }
}