#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nb_streams; TYPE_3__** streams; } ;
struct TYPE_6__ {int den; int const num; } ;
struct TYPE_8__ {TYPE_1__ sample_aspect_ratio; } ;
struct TYPE_7__ {TYPE_5__* fc; } ;
typedef  TYPE_2__ MOVContext ;
typedef  int /*<<< orphan*/  MOVAtom ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int const,int const,int const,int const) ; 
 int /*<<< orphan*/  av_reduce (int const*,int const*,int const,int const,int) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mov_read_pasp(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    const int num = avio_rb32(pb);
    const int den = avio_rb32(pb);
    AVStream *st;

    if (c->fc->nb_streams < 1)
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];

    if ((st->sample_aspect_ratio.den != 1 || st->sample_aspect_ratio.num) && // default
        (den != st->sample_aspect_ratio.den || num != st->sample_aspect_ratio.num)) {
        av_log(c->fc, AV_LOG_WARNING,
               "sample aspect ratio already set to %d:%d, ignoring 'pasp' atom (%d:%d)\n",
               st->sample_aspect_ratio.num, st->sample_aspect_ratio.den,
               num, den);
    } else if (den != 0) {
        av_reduce(&st->sample_aspect_ratio.num, &st->sample_aspect_ratio.den,
                  num, den, 32767);
    }
    return 0;
}