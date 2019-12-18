#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int nb_streams; size_t ist_index; TYPE_1__* ctx; } ;
struct TYPE_14__ {scalar_t__ user_set_discard; } ;
struct TYPE_13__ {TYPE_2__* codecpar; } ;
struct TYPE_12__ {int channel_idx; int ofile_idx; int ostream_idx; int file_idx; int stream_idx; } ;
struct TYPE_11__ {int nb_audio_channel_maps; TYPE_4__* audio_channel_maps; } ;
struct TYPE_10__ {scalar_t__ codec_type; int channels; } ;
struct TYPE_9__ {TYPE_5__** streams; } ;
typedef  TYPE_3__ OptionsContext ;
typedef  TYPE_4__ AudioChannelMap ;
typedef  TYPE_5__ AVStream ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GROW_ARRAY (TYPE_4__*,int) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 char* av_strdup (char const*) ; 
 int /*<<< orphan*/  exit_program (int) ; 
 TYPE_7__** input_files ; 
 TYPE_6__** input_streams ; 
 int nb_input_files ; 
 int sscanf (char const*,char*,int*,int*,int*,...) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int opt_map_channel(void *optctx, const char *opt, const char *arg)
{
    OptionsContext *o = optctx;
    int n;
    AVStream *st;
    AudioChannelMap *m;
    char *allow_unused;
    char *mapchan;
    mapchan = av_strdup(arg);
    if (!mapchan)
        return AVERROR(ENOMEM);

    GROW_ARRAY(o->audio_channel_maps, o->nb_audio_channel_maps);
    m = &o->audio_channel_maps[o->nb_audio_channel_maps - 1];

    /* muted channel syntax */
    n = sscanf(arg, "%d:%d.%d", &m->channel_idx, &m->ofile_idx, &m->ostream_idx);
    if ((n == 1 || n == 3) && m->channel_idx == -1) {
        m->file_idx = m->stream_idx = -1;
        if (n == 1)
            m->ofile_idx = m->ostream_idx = -1;
        av_free(mapchan);
        return 0;
    }

    /* normal syntax */
    n = sscanf(arg, "%d.%d.%d:%d.%d",
               &m->file_idx,  &m->stream_idx, &m->channel_idx,
               &m->ofile_idx, &m->ostream_idx);

    if (n != 3 && n != 5) {
        av_log(NULL, AV_LOG_FATAL, "Syntax error, mapchan usage: "
               "[file.stream.channel|-1][:syncfile:syncstream]\n");
        exit_program(1);
    }

    if (n != 5) // only file.stream.channel specified
        m->ofile_idx = m->ostream_idx = -1;

    /* check input */
    if (m->file_idx < 0 || m->file_idx >= nb_input_files) {
        av_log(NULL, AV_LOG_FATAL, "mapchan: invalid input file index: %d\n",
               m->file_idx);
        exit_program(1);
    }
    if (m->stream_idx < 0 ||
        m->stream_idx >= input_files[m->file_idx]->nb_streams) {
        av_log(NULL, AV_LOG_FATAL, "mapchan: invalid input file stream index #%d.%d\n",
               m->file_idx, m->stream_idx);
        exit_program(1);
    }
    st = input_files[m->file_idx]->ctx->streams[m->stream_idx];
    if (st->codecpar->codec_type != AVMEDIA_TYPE_AUDIO) {
        av_log(NULL, AV_LOG_FATAL, "mapchan: stream #%d.%d is not an audio stream.\n",
               m->file_idx, m->stream_idx);
        exit_program(1);
    }
    /* allow trailing ? to map_channel */
    if (allow_unused = strchr(mapchan, '?'))
        *allow_unused = 0;
    if (m->channel_idx < 0 || m->channel_idx >= st->codecpar->channels ||
        input_streams[input_files[m->file_idx]->ist_index + m->stream_idx]->user_set_discard == AVDISCARD_ALL) {
        if (allow_unused) {
            av_log(NULL, AV_LOG_VERBOSE, "mapchan: invalid audio channel #%d.%d.%d\n",
                    m->file_idx, m->stream_idx, m->channel_idx);
        } else {
            av_log(NULL, AV_LOG_FATAL,  "mapchan: invalid audio channel #%d.%d.%d\n"
                    "To ignore this, add a trailing '?' to the map_channel.\n",
                    m->file_idx, m->stream_idx, m->channel_idx);
            exit_program(1);
        }

    }
    av_free(mapchan);
    return 0;
}