#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_19__ {scalar_t__ eof_reached; } ;
struct TYPE_18__ {TYPE_1__* priv_data; } ;
struct TYPE_17__ {TYPE_12__* fc; } ;
struct TYPE_16__ {unsigned int rap_group_count; TYPE_11__* rap_group; } ;
struct TYPE_15__ {int nb_streams; TYPE_3__** streams; } ;
struct TYPE_14__ {void* index; void* count; } ;
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
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_free (TYPE_11__*) ; 
 int /*<<< orphan*/  av_log (TYPE_12__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_11__* av_malloc_array (unsigned int,int) ; 
 int avio_r8 (TYPE_4__*) ; 
 int /*<<< orphan*/  avio_rb24 (TYPE_4__*) ; 
 void* avio_rb32 (TYPE_4__*) ; 
 scalar_t__ avio_rl32 (TYPE_4__*) ; 

__attribute__((used)) static int mov_read_sbgp(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    MOVStreamContext *sc;
    unsigned int i, entries;
    uint8_t version;
    uint32_t grouping_type;

    if (c->fc->nb_streams < 1)
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];
    sc = st->priv_data;

    version = avio_r8(pb); /* version */
    avio_rb24(pb); /* flags */
    grouping_type = avio_rl32(pb);
    if (grouping_type != MKTAG( 'r','a','p',' '))
        return 0; /* only support 'rap ' grouping */
    if (version == 1)
        avio_rb32(pb); /* grouping_type_parameter */

    entries = avio_rb32(pb);
    if (!entries)
        return 0;
    if (sc->rap_group)
        av_log(c->fc, AV_LOG_WARNING, "Duplicated SBGP atom\n");
    av_free(sc->rap_group);
    sc->rap_group_count = 0;
    sc->rap_group = av_malloc_array(entries, sizeof(*sc->rap_group));
    if (!sc->rap_group)
        return AVERROR(ENOMEM);

    for (i = 0; i < entries && !pb->eof_reached; i++) {
        sc->rap_group[i].count = avio_rb32(pb); /* sample_count */
        sc->rap_group[i].index = avio_rb32(pb); /* group_description_index */
    }

    sc->rap_group_count = i;

    if (pb->eof_reached) {
        av_log(c->fc, AV_LOG_WARNING, "reached eof, corrupted SBGP atom\n");
        return AVERROR_EOF;
    }

    return 0;
}