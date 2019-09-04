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
struct TYPE_13__ {int /*<<< orphan*/  pb; } ;
struct TYPE_12__ {int /*<<< orphan*/  priv_data; TYPE_1__* codecpar; int /*<<< orphan*/  duration; int /*<<< orphan*/  start_time; scalar_t__ id; } ;
struct TYPE_11__ {int /*<<< orphan*/  codec_type; int /*<<< orphan*/  bit_rate; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_DATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avio_rb16 (int /*<<< orphan*/ *) ; 
 unsigned int avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  ff_rm_alloc_rmstream () ; 
 int ff_rm_read_mdpr_codecdata (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rm_read_multi(AVFormatContext *s, AVIOContext *pb,
                         AVStream *st, char *mime)
{
    int number_of_streams = avio_rb16(pb);
    int number_of_mdpr;
    int i, ret;
    unsigned size2;
    for (i = 0; i<number_of_streams; i++)
        avio_rb16(pb);
    number_of_mdpr = avio_rb16(pb);
    if (number_of_mdpr != 1) {
        avpriv_request_sample(s, "MLTI with multiple (%d) MDPR", number_of_mdpr);
    }
    for (i = 0; i < number_of_mdpr; i++) {
        AVStream *st2;
        if (i > 0) {
            st2 = avformat_new_stream(s, NULL);
            if (!st2) {
                ret = AVERROR(ENOMEM);
                return ret;
            }
            st2->id = st->id + (i<<16);
            st2->codecpar->bit_rate = st->codecpar->bit_rate;
            st2->start_time = st->start_time;
            st2->duration   = st->duration;
            st2->codecpar->codec_type = AVMEDIA_TYPE_DATA;
            st2->priv_data = ff_rm_alloc_rmstream();
            if (!st2->priv_data)
                return AVERROR(ENOMEM);
        } else
            st2 = st;

        size2 = avio_rb32(pb);
        ret = ff_rm_read_mdpr_codecdata(s, s->pb, st2, st2->priv_data,
                                        size2, NULL);
        if (ret < 0)
            return ret;
    }
    return 0;
}