#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_13__ {int has_primaries; int has_luminance; void* min_luminance; void* max_luminance; void** white_point; void*** display_primaries; } ;
struct TYPE_12__ {int size; } ;
struct TYPE_11__ {TYPE_8__* fc; } ;
struct TYPE_10__ {TYPE_7__* mastering; } ;
struct TYPE_9__ {TYPE_2__* priv_data; } ;
typedef  TYPE_2__ MOVStreamContext ;
typedef  TYPE_3__ MOVContext ;
typedef  TYPE_4__ MOVAtom ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*,...) ; 
 void* av_make_q (int /*<<< orphan*/ ,int) ; 
 TYPE_7__* av_mastering_display_metadata_alloc () ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mov_read_smdm(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    MOVStreamContext *sc;
    int i, version;

    if (c->fc->nb_streams < 1)
        return AVERROR_INVALIDDATA;

    sc = c->fc->streams[c->fc->nb_streams - 1]->priv_data;

    if (atom.size < 5) {
        av_log(c->fc, AV_LOG_ERROR, "Empty Mastering Display Metadata box\n");
        return AVERROR_INVALIDDATA;
    }

    version = avio_r8(pb);
    if (version) {
        av_log(c->fc, AV_LOG_WARNING, "Unsupported Mastering Display Metadata box version %d\n", version);
        return 0;
    }
    avio_skip(pb, 3); /* flags */

    sc->mastering = av_mastering_display_metadata_alloc();
    if (!sc->mastering)
        return AVERROR(ENOMEM);

    for (i = 0; i < 3; i++) {
        sc->mastering->display_primaries[i][0] = av_make_q(avio_rb16(pb), 1 << 16);
        sc->mastering->display_primaries[i][1] = av_make_q(avio_rb16(pb), 1 << 16);
    }
    sc->mastering->white_point[0] = av_make_q(avio_rb16(pb), 1 << 16);
    sc->mastering->white_point[1] = av_make_q(avio_rb16(pb), 1 << 16);

    sc->mastering->max_luminance = av_make_q(avio_rb32(pb), 1 << 8);
    sc->mastering->min_luminance = av_make_q(avio_rb32(pb), 1 << 14);

    sc->mastering->has_primaries = 1;
    sc->mastering->has_luminance = 1;

    return 0;
}