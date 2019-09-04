#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  scheme; } ;
struct TYPE_15__ {int nb_streams; TYPE_5__** streams; } ;
struct TYPE_14__ {TYPE_2__* priv_data; } ;
struct TYPE_13__ {int size; } ;
struct TYPE_12__ {TYPE_8__* fc; } ;
struct TYPE_10__ {TYPE_9__* default_encrypted_sample; } ;
struct TYPE_11__ {scalar_t__ pseudo_stream_id; TYPE_1__ cenc; } ;
typedef  TYPE_2__ MOVStreamContext ;
typedef  TYPE_3__ MOVContext ;
typedef  TYPE_4__ MOVAtom ;
typedef  TYPE_5__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_9__* av_encryption_info_alloc (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  av_log (TYPE_8__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_rb32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mov_read_schm(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    MOVStreamContext *sc;

    if (c->fc->nb_streams < 1)
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];
    sc = st->priv_data;

    if (sc->pseudo_stream_id != 0) {
        av_log(c->fc, AV_LOG_ERROR, "schm boxes are only supported in first sample descriptor\n");
        return AVERROR_PATCHWELCOME;
    }

    if (atom.size < 8)
        return AVERROR_INVALIDDATA;

    avio_rb32(pb); /* version and flags */

    if (!sc->cenc.default_encrypted_sample) {
        sc->cenc.default_encrypted_sample = av_encryption_info_alloc(0, 16, 16);
        if (!sc->cenc.default_encrypted_sample) {
            return AVERROR(ENOMEM);
        }
    }

    sc->cenc.default_encrypted_sample->scheme = avio_rb32(pb);
    return 0;
}