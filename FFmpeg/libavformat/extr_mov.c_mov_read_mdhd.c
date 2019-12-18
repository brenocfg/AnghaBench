#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* int64_t ;
struct TYPE_11__ {int nb_streams; TYPE_3__** streams; } ;
struct TYPE_10__ {int /*<<< orphan*/  metadata; void* duration; TYPE_1__* priv_data; } ;
struct TYPE_9__ {TYPE_5__* fc; } ;
struct TYPE_8__ {int time_scale; } ;
typedef  TYPE_1__ MOVStreamContext ;
typedef  TYPE_2__ MOVContext ;
typedef  int /*<<< orphan*/  MOVAtom ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 unsigned int avio_rb16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb24 (int /*<<< orphan*/ *) ; 
 void* avio_rb32 (int /*<<< orphan*/ *) ; 
 void* avio_rb64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_5__*,char*,int) ; 
 scalar_t__ ff_mov_lang_to_iso639 (unsigned int,char*) ; 
 int /*<<< orphan*/  mov_metadata_creation_time (int /*<<< orphan*/ *,void*,TYPE_5__*) ; 

__attribute__((used)) static int mov_read_mdhd(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    MOVStreamContext *sc;
    int version;
    char language[4] = {0};
    unsigned lang;
    int64_t creation_time;

    if (c->fc->nb_streams < 1)
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];
    sc = st->priv_data;

    if (sc->time_scale) {
        av_log(c->fc, AV_LOG_ERROR, "Multiple mdhd?\n");
        return AVERROR_INVALIDDATA;
    }

    version = avio_r8(pb);
    if (version > 1) {
        avpriv_request_sample(c->fc, "Version %d", version);
        return AVERROR_PATCHWELCOME;
    }
    avio_rb24(pb); /* flags */
    if (version == 1) {
        creation_time = avio_rb64(pb);
        avio_rb64(pb);
    } else {
        creation_time = avio_rb32(pb);
        avio_rb32(pb); /* modification time */
    }
    mov_metadata_creation_time(&st->metadata, creation_time, c->fc);

    sc->time_scale = avio_rb32(pb);
    if (sc->time_scale <= 0) {
        av_log(c->fc, AV_LOG_ERROR, "Invalid mdhd time scale %d, defaulting to 1\n", sc->time_scale);
        sc->time_scale = 1;
    }
    st->duration = (version == 1) ? avio_rb64(pb) : avio_rb32(pb); /* duration */

    lang = avio_rb16(pb); /* language */
    if (ff_mov_lang_to_iso639(lang, language))
        av_dict_set(&st->metadata, "language", language, 0);
    avio_rb16(pb); /* quality */

    return 0;
}