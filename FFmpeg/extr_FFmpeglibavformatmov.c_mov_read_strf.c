#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_12__ {int /*<<< orphan*/  extradata; } ;
struct TYPE_11__ {int nb_streams; TYPE_3__** streams; } ;
struct TYPE_10__ {TYPE_7__* codecpar; } ;
struct TYPE_9__ {int size; } ;
struct TYPE_8__ {TYPE_6__* fc; } ;
typedef  TYPE_1__ MOVContext ;
typedef  TYPE_2__ MOVAtom ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int ff_get_extradata (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mov_read_strf(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    int ret;

    if (c->fc->nb_streams < 1)
        return 0;
    if (atom.size <= 40)
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];

    if ((uint64_t)atom.size > (1<<30))
        return AVERROR_INVALIDDATA;

    avio_skip(pb, 40);
    av_freep(&st->codecpar->extradata);
    ret = ff_get_extradata(c->fc, st->codecpar, pb, atom.size - 40);
    if (ret < 0)
        return ret;

    return 0;
}