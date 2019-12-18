#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int nb_streams; TYPE_3__** streams; } ;
struct TYPE_12__ {scalar_t__ eof_reached; } ;
struct TYPE_11__ {TYPE_1__* priv_data; } ;
struct TYPE_10__ {TYPE_8__* fc; } ;
struct TYPE_9__ {unsigned int stps_count; void** stps_data; } ;
typedef  TYPE_1__ MOVStreamContext ;
typedef  TYPE_2__ MOVContext ;
typedef  int /*<<< orphan*/  MOVAtom ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (void**) ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 void** av_malloc_array (unsigned int,int) ; 
 void* avio_rb32 (TYPE_4__*) ; 

__attribute__((used)) static int mov_read_stps(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    MOVStreamContext *sc;
    unsigned i, entries;

    if (c->fc->nb_streams < 1)
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];
    sc = st->priv_data;

    avio_rb32(pb); // version + flags

    entries = avio_rb32(pb);
    if (sc->stps_data)
        av_log(c->fc, AV_LOG_WARNING, "Duplicated STPS atom\n");
    av_free(sc->stps_data);
    sc->stps_count = 0;
    sc->stps_data = av_malloc_array(entries, sizeof(*sc->stps_data));
    if (!sc->stps_data)
        return AVERROR(ENOMEM);

    for (i = 0; i < entries && !pb->eof_reached; i++) {
        sc->stps_data[i] = avio_rb32(pb);
    }

    sc->stps_count = i;

    if (pb->eof_reached) {
        av_log(c->fc, AV_LOG_WARNING, "reached eof, corrupted STPS atom\n");
        return AVERROR_EOF;
    }

    return 0;
}